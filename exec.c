#include "pipex.h"

//./pipex Makfile cat cat outFile

void    launch_pipe(t_data *data)
{
    if (pipe(data->pipe) == -1)
        error(data, "Failed to create a pipe", 1);
}

void    execute_cmd(t_data *data, t_cmd *cmd)
{
    (void)data;
    execve(cmd->path, cmd->args, environ);
    perror(cmd->path);
    exit(1);
}

void    manage_fds(t_data *data, t_cmd *cmd)
{
    if (cmd == data->head_cmd)
        make_input(data->input_file);
    else
        make_input(data->pipe[0]);
    if (cmd->next)
        make_output(data->pipe[1]);
    else
        make_output(data->output_file);
    printf("passed here\n");//debug
}

void    close_fds(t_data *data)
{
    if (data->input_file != -1)
    {
        close(data->input_file);
        data->input_file = -1;
    }
    if (data->output_file != -1)
    {
        close(data->output_file);
        data->output_file = -1;
    }
    if (data->pipe[0] != -1)
    {
        close(data->pipe[0]);
        data->pipe[0] = -1;
    }
    if (data->pipe[1] != -1)
    {
        close(data->pipe[1]);
        data->pipe[1] = -1;
    }
}

//debug:

void    manage_pipes(t_data *data, int i)
{
    if (i % 2 == 0)
    {
        if (pipe(data->pipe) == -1)
            error(data, "Failed to create a pipe", 1);
    }
}

void    execute_cmds(t_data *data)
{
    t_cmd   *curr_cmd;
    int     i;

    i = 0;
    while (curr_cmd)
    {
        printf("iterating number %d\n", i);
        manage_pipes(data, i);
        manage_fds(data, curr_cmd);
        data->child_pid = fork();
        if (data->child_pid == -1)
            error(data, "Failed to create a child process", 1);
        if (data->child_pid == 0)
            execute_cmd(data, curr_cmd);
        else
        {
            if (curr_cmd->next)
                close(data->pipe[1]);
            if (curr_cmd != data->head_cmd)
                close(data->pipe[0]);
            curr_cmd = curr_cmd->next;
        }
        i++;
    }
    while (wait(NULL) > 0);
    close_fds(data);
}
