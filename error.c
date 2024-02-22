#include "pipex.h"

void    exit_with_message(char *message, t_tracker *tracker)
{
    if (tracker->path != NULL)
        free_split(tracker->path);
    if (tracker->cmd1 != NULL)
        free_split(tracker->cmd1);
    if (tracker->cmd2 != NULL)
        free_split(tracker->cmd2);
    if (tracker->cmd1_path)
        free(tracker->cmd1_path);
    if (tracker->cmd2_path)
        free(tracker->cmd2_path);
    if (tracker->in_fd != -1)
        close(tracker->in_fd);
    if (tracker->out_fd != -1
        && tracker->out_fd != tracker->in_fd)
        close(tracker->out_fd);
    if (!message)
        exit(1);
    write(2, "Error: ", 7);
    write(2, message, ft_strlen(message));
    write(2, "\n", 1);
    exit(1);
}
