#include "pipex.h"

void    error(t_data *data, char *msg, int status)
{
    write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
    free_all(data);
    exit(status);
}