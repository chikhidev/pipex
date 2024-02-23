#include "pipex.h"

void free_split(char **split)
{
    int i;

    i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

void free_all(t_tracker *tracker)
{
    if (tracker->path != NULL)
        free_split(tracker->path);
    if (tracker->cmd1 != NULL)
        free_split(tracker->cmd1);
    if (tracker->cmd2 != NULL)
        free_split(tracker->cmd2);
    if (tracker->cmd1_path != NULL)
        free(tracker->cmd1_path);
    if (tracker->cmd2_path != NULL)
        free(tracker->cmd2_path);
    if (tracker->in_fd != -1)
        close(tracker->in_fd);
    if (tracker->out_fd != -1 && tracker->out_fd != tracker->in_fd)
        close(tracker->out_fd);
}
