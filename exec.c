#include "pipex.h"

//./pipex Makfile cat cat outFile

void    execute_cmd(t_data *data, t_cmd *cmd)
{
    (void)data;
    execve(cmd->path, cmd->args, environ);
    perror(cmd->path);
    exit(1);
}

void    manage_pipe(t_data *data, t_cmd *cmd)
{
    if (pipe(cmd->pipe) == -1)
        error(data, "Failed to create a pipe", 1);
    if (cmd->prev)
        dup2(cmd->prev->pipe[0], 0);
    else
        dup2(data->input_file, 0);
    if (cmd->next)
        dup2(cmd->pipe[1], 1);
    else
        dup2(data->output_file, 1);
}

void    execute_cmds(t_data *data)
{
    t_cmd   *curr_cmd;

    curr_cmd = data->head_cmd;
    while (curr_cmd)
    {
        manage_pipe(data, curr_cmd);
        data->child_pid = fork();
        if (data->child_pid == -1)
            error(data, "Failed to create a child process", 1);
        if (data->child_pid == 0)
            execute_cmd(data, curr_cmd);
        curr_cmd = curr_cmd->next;
        write(2, "_______________________________\n", 33);
    }
    write(2, "waiting\n", 9); // debug
    wait(NULL);
}
