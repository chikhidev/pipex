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
            exit_with_message("Error", tracker);
        }
        if (execve(cmd->cmd_path, cmd->cmd_args, environ) == -1)
        {
            perror(cmd->cmd_path);
            exit_with_message("Error", tracker);
        }
        free_all(tracker);
        exit(0);
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


    // ft_printf("in_fd: %d\n", tracker->in_fd);
    // ft_printf("out_fd: %d\n", tracker->out_fd);
    // ft_printf("pipe read end: %d\n", tracker->pipe_fd[0]);
    // ft_printf("pipe write end: %d\n", tracker->pipe_fd[1]);
    // ft_printf("------------------------------------------------\n");

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

        if (tracker->current_process_id > 0 && cmd->next)
            waitpid(tracker->current_process_id, NULL, 0);

        // write(2, "in cmd number ", 15);
        // write(2, ft_itoa(i), ft_strlen(ft_itoa(i)));
        // write(2, "\n", 1);
        // write(2, "input file ", 11);
        // write(2, ft_itoa(tracker->in), ft_strlen(ft_itoa(tracker->in)));
        // write(2, "\n", 1);
        // write(2, "output file ", 12);
        // write(2, ft_itoa(tracker->out), ft_strlen(ft_itoa(tracker->out)));
        // write(2, "\n", 1);
        

        // write(2, "waiting for process ", 21);
        // write(2, ft_itoa(tracker->current_process_id), ft_strlen(ft_itoa(tracker->current_process_id)));
        // write(2, " to finish\n", 11);

        tracker->current_process_id = -1;

        // write(2, "passed, to next command\n", 25);
        // write(2, "-------------------------\n", 26);
        cmd = cmd->next;
        i++;
    }

    close(tracker->pipe_fd[0]);
    close(tracker->pipe_fd[1]);
    close(tracker->in_fd);
    close(tracker->out_fd);
}
