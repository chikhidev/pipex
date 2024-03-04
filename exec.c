#include "pipex.h"

//./pipex Makfile cat cat outFile

void    execute_cmd(t_data *data, t_cmd *cmd)
{
    if (cmd == data->head_cmd)
        dup2(data->input_file, 0);
    else
        dup2(data->pipe[0], 0);
    if (cmd->next)
        dup2(data->pipe[1], 1);
    else
        dup2(data->output_file, 1);
    execve(cmd->path, cmd->args, environ);
    error(data, "Failed to execute the command", 1);
}

void    execute_cmds(t_data *data)
{
    t_cmd   *curr_cmd;

    if (pipe(data->pipe) == -1)
        error(data, "Failed to create pipe", 1);
    curr_cmd = data->head_cmd;
    while (curr_cmd)
    {
        data->child_pid = fork();
        if (data->child_pid == -1)
            error(data, "Failed to create a child process", 1);
        if (data->child_pid == 0)
            execute_cmd(data, curr_cmd);
        else
        {
            waitpid(data->child_pid, NULL, 0);
            curr_cmd = curr_cmd->next;
        }
    }
}
