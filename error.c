#include "pipex.h"

void    error(char *msg, int status)
{
    write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
    exit(status);
}