#include "pipex.h"

void    exit_with_message(char *message, t_tracker *tracker)
{
    free_all(tracker);
    if (!message)
        exit(1);
    write(2, "Error: ", 7);
    write(2, message, ft_strlen(message));
    write(2, "\n", 1);
    exit(1);
}
