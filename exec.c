#include "pipex.h"

void    wait_all_processes(t_tracker *tracker)
{
    t_command   *cmd;


    cmd = tracker->first_command;
    while (cmd)
    {
        if (cmd->pid != -1)
            waitpid(cmd->pid, NULL, 0);
        cmd = tracker->first_command->next;
    }
}

void    execute_command(t_tracker *tracker, t_command *cmd)
{
    if (access(cmd->cmd_path, F_OK) == -1)
    {
        ft_printf("%s: no such file\n", cmd->cmd_args[0]);
        return ;
    }
    cmd->pid = fork();
    if (cmd->pid == -1)
        exit_with_message("fork failed", tracker);
    if (cmd->pid == 0)
    {
        execve(cmd->cmd_path, cmd->cmd_args, environ);
        ft_printf("enable to execute %s\n", cmd);
    }
}

void    execute_commands(t_tracker *tracker)
{
    int         stdin;
    int         stdout;
    t_command   *cmd;

    // stdin = dup(0);
    // stdout = dup(1);
    // if (pipe(tracker->pipe_fd) == -1)
    //     exit_with_message("pipe failed", tracker);

    while (cmd)
    {
        execute_command(tracker, cmd);
        cmd = cmd->next;
    }
    
    wait_all_processes(tracker);

    // close(tracker->pipe_fd[0]);
    // close(tracker->in_fd);
    // close(tracker->out_fd);

    // dup2(stdin, 0);
    // dup2(stdout, 1);
    // close(stdin);
    // close(stdout);
}
