#include "pipex.h"

//./pipex Makfile cat cat outFile

void    execute_cmd(t_data *data, t_cmd *cmd)
{
    if (pipe(cmd->entries) < 0)
        error(data, "pipe failed", 1);
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
    t_cmd   *next_cmd;
    int     cmd_index;

    cmd_index = 0;
    curr_cmd = data->head_cmd;
    while (curr_cmd)
    {
        // execute_cmd(data, curr_cmd);
        printf("cmd_index: %d\n", cmd_index);
        printf("cmd: %s\n", curr_cmd->path);
        for (int i = 0; curr_cmd->args[i]; i++)
            printf("args[%d]: %s\n", i, curr_cmd->args[i]);
        printf("--------------------\n");
        next_cmd = curr_cmd->next;
        free(curr_cmd);
        curr_cmd = next_cmd;
        if (curr_cmd)
            curr_cmd->prev = NULL;
        cmd_index += 1;
    }
    wait(NULL);
}
