#include "pipex.h"

void    validate_in_out_files (char **av, int ac, t_tracker *tracker)
{
    if (access(av[1], F_OK) == -1)
        exit_with_message("Input file does not exist", tracker);
    if (access(av[1], R_OK) == -1)
        exit_with_message("No permission to read from input file", tracker);
    tracker->in_fd = open(av[1], O_RDONLY);
    if (tracker->in_fd == -1)
        exit_with_message("Invalid input file", tracker);
    if (access(av[ac - 1], F_OK) == -1)
        tracker->out_fd = open(av[ac - 1], O_CREAT | O_WRONLY, 0644);
    else
    {
        if (access(av[ac - 1], W_OK) == -1)
            exit_with_message("No permission to write to output file", tracker);
        tracker->out_fd = open(av[ac - 1], O_WRONLY | O_TRUNC);
        if (tracker->out_fd == -1)
            exit_with_message("Invalid output file", tracker);
    }
}