#include "./pipex_bonus.h"

void    ft_close(int *fd)
{
    if (*fd != -1)
    {
        close(*fd);
        *fd = -1;
    }
}

void    error(t_data *data, char *msg, int status)
{
    int len;
    int i;

    i = 5;
    len = ft_strlen(msg);
    write(2, "Error", 6);
    while (i < len)
    {
        write(2, "-", 1);
        i++;
    }
    write(2, "\n", 1);
    write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
    i = 0;
    while (i < len)
    {
        write(2, "-", 1);
        i++;
    }
    write(2, "\n", 1);
    free_all(data);
    exit(status);
}
