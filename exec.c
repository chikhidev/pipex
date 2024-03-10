#include "pipex.h"

//./pipex Makfile cat cat outFile

void    manage_fds(t_data *data, t_cmd *cmd)
{
    if (cmd->prev)
        make_input(cmd->prev->entries[1]);
    else
        make_input(data->input_file);
    if (cmd->next)
        make_output(cmd->entries[0]);
    else
        make_output(data->output_file);
}

void    execute_cmd(t_data *data, t_cmd *cmd)
{
    data->child_pid = fork();
    if (data->child_pid < 0)
        error(data, "fork failed", 1);
    if (data->child_pid == 0)
    {
        execve(cmd->path, cmd->args, environ);
        perror(cmd->path);
        exit(1);
    }
}

void    execute_cmds(t_data *data)
{
    t_cmd   *curr_cmd;
    int     cmd_index;

    cmd_index = 0;
    curr_cmd = data->head_cmd;
    while (curr_cmd)
    {
        manage_fds(data, curr_cmd);
        execute_cmd(data, curr_cmd);

        // //debug
        // printf("cmd_index: %d\n", cmd_index);
        // printf("cmd: %s\n", curr_cmd->path);
        // for (int i = 0; curr_cmd->args[i]; i++)
        //     printf("args[%d]: %s\n", i, curr_cmd->args[i]);
        // printf("--------------------\n");
        // //debug

        curr_cmd = curr_cmd->next;
        if (curr_cmd)
            curr_cmd->prev = NULL;
        cmd_index += 1;
    }
    wait(NULL);
}
