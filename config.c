#include "pipex.h"

void    init_tracker(t_tracker *tracker)
{
    tracker->in_fd = -1;
    tracker->out_fd = -1;
    tracker->is_path_available = 0;
    tracker->cmd1_path = NULL;
    tracker->cmd2_path = NULL;
    tracker->path = NULL;
}

// void    look_for_command(t_tracker *tracker)
// {
//     char    *path;

//     path = NULL;
//     if (tracker->is_path_available)
//         path = getenv("PATH");
    
// }