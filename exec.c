#include "pipex.h"

//./pipex Makfile cat cat outFile

void    execute_cmd(t_data *data, t_cmd *cmd)
{
    (void)data;
    execve(cmd->path, cmd->args, environ);
    perror(cmd->path);
    exit(1);
}


void    execute_cmds(t_data *data)
{
    t_cmd   *curr_cmd;

    curr_cmd = data->head_cmd;
    while (curr_cmd)
    {

    }
    wait(NULL);
}
