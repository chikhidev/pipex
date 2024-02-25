#include "pipex.h"

void    init_tracker(t_tracker *tracker)
{
    tracker->in_fd = -1;
    tracker->out_fd = -1;
    tracker->is_path_available = 0;
    tracker->first_command = NULL;
    tracker->path = NULL;
    tracker->pipe_fd[0] = -1;
    tracker->pipe_fd[1] = -1;
}
