#include "pipex.h"

void    exit_with_message(char *message, t_tracker *tracker)
{
    int i;

    i = 0;
    if (tracker->path != NULL)
    {
        while (tracker->path[i])
        {
            free(tracker->path[i]);
            i++;
        }
        free(tracker->path);
    }
    if (tracker->cmd1_path)
        free(tracker->cmd1_path);
    if (tracker->cmd2_path)
        free(tracker->cmd2_path);
    if (!message)
        exit(1);
    write(2, "Error: ", 7);
    write(2, message, ft_strlen(message));
    write(2, "\n", 1);
    system("valgrind --leak-check=yes ./pipex");
    exit(1);
}