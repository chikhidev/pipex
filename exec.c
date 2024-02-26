#include "pipex.h"

void    wait_all_processes(t_tracker *tracker)
{
    t_command   *cmd;


    cmd = tracker->first_command;
    while (cmd)
    {
        if (cmd->pid != -1)
            waitpid(cmd->pid, NULL, 0);
        cmd = cmd->next;
    }
}

void    execute_command(t_tracker *tracker, t_command *cmd)
{
    cmd->pid = fork();
    if (cmd->pid == -1)
        exit_with_message("Error: fork failed", tracker);
    if (cmd->pid == 0)
    {
        if (execve(cmd->cmd_path, cmd->cmd_args, environ) == -1)
            perror(cmd->cmd_path);
        exit(1);
    }
}

void    execute_commands(t_tracker *tracker)
{
    int         stdin;
    int         stdout;
    t_command   *cmd;

    cmd = tracker->first_command;
    while (cmd)
    {
        execute_command(tracker, cmd);
        cmd = cmd->next;
    }

    wait_all_processes(tracker);
}
