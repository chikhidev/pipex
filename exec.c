#include "pipex.h"

void    execute_command(t_tracker *tracker, t_command *cmd)
{
    tracker->current_process_id = fork();
    if (tracker->current_process_id == -1)
        exit_with_message("Error: fork failed", tracker);
    if (tracker->current_process_id == 0)
    {
        if (cmd->cmd_path == NULL)
        {
            perror("pipex: command not valid");
            exit(1);
        }
        if (execve(cmd->cmd_path, cmd->cmd_args, environ) == -1)
            perror(cmd->cmd_path);
        exit(1);
    }
}

void    execute_commands(t_tracker *tracker)
{
    t_command   *cmd;
    int     i;

    i = 0;
    cmd = tracker->first_command;

    if (pipe(tracker->pipe_fd) == -1)
        perror("Pipe error");


    while (cmd)
    {
        if (i == 0)
            tracker->in = tracker->in_fd;
        else
            tracker->in = tracker->pipe_fd[0];
        if (cmd->next)
            tracker->out = tracker->pipe_fd[1];
        else
            tracker->out = tracker->out_fd;

        dup2(tracker->in, 0);
        dup2(tracker->out, 1);
        execute_command(tracker, cmd);
        waitpid(tracker->current_process_id, NULL, 0);
        cmd = cmd->next;
        i++;
    }

    close(tracker->pipe_fd[0]);
    close(tracker->pipe_fd[1]);
    close(tracker->in_fd);
    close(tracker->out_fd);
}
