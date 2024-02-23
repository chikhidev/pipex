#include "pipex.h"

void    execute_command(t_tracker *tracker, char *cmd, char **args, int *pid)
{
    *pid = fork();
    if (*pid == -1)
        exit_with_message("fork failed", tracker);
    if (*pid == 0)
    {
        execve(cmd, args, environ);
        ft_printf("enable to execute %s\n", cmd);
        exit_with_message("execve failed", tracker);
    }
}

void    handle_execution(t_tracker *tracker)
{
    int pid1;
    int pid2;
    int stdin;
    int stdout;

    stdin = dup(0);
    stdout = dup(1);
    if (pipe(tracker->pipe_fd) == -1)
        exit_with_message("pipe failed", tracker);
    dup2(tracker->pipe_fd[1], 1);
    dup2(tracker->in_fd, 0);
    execute_command(tracker, tracker->cmd1_path, tracker->cmd1, &pid1);
    close(tracker->pipe_fd[1]);
    dup2(tracker->pipe_fd[0], 0);
    dup2(tracker->out_fd, 1);
    execute_command(tracker, tracker->cmd2_path, tracker->cmd2, &pid2);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    close(tracker->pipe_fd[0]);
    close(tracker->in_fd);
    close(tracker->out_fd);
    dup2(stdin, 0);
    dup2(stdout, 1);
    close(stdin);
    close(stdout);
}
