#include "pipex.h"

void    execute_command(t_tracker *tracker, char *cmd, char **args)
{
    int pid;

    pid = fork();
    if (pid == -1)
        exit_with_message("fork failed", tracker);
    if (pid == 0)
    {
        printf("executing %s...\n", cmd);
        execve(cmd, args, environ);
        ft_printf("enable to execute %s\n", cmd);
        exit_with_message("execve failed", tracker);
    }
    else
        wait(NULL);
}

void    handle_execution(t_tracker *tracker)
{
    dup2(tracker->in_fd, 0);
    dup2(tracker->out_fd, 1);

    /*logic of executing*/
    execute_command(tracker, tracker->cmd1_path, tracker->cmd1);
    execute_command(tracker, tracker->cmd2_path, tracker->cmd2);

    /*closing fds to prevent problems*/
    close(tracker->in_fd);
    close(tracker->out_fd);
}
