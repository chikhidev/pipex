#include "pipex.h"

void    validate_in_out_files (char **av, int ac, t_tracker *tracker)
{
    tracker->in_fd = open(av[1], O_RDONLY);
    if (tracker->in_fd == -1)
        exit_with_message("Invalid input file", tracker);
    tracker->out_fd = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC);
    if (tracker->out_fd == -1)
        exit_with_message("Invalid output file", tracker);
}