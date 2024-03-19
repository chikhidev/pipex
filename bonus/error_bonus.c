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
    write(2, "Error: ", 8);
    write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
    free_all(data);
    exit(1);
}
