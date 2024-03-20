#include "./pipex_bonus.h"

void    ft_close(int *fd)
{
    if (*fd != -1)
    {
        close(*fd);
        *fd = -1;
    }
}

void    error(t_data *data, char *msg)
{
    perror(msg);
    free_all(data);
    exit(1);
}
