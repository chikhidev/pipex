#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
#include <sys/types.h>

#include "libft/libft.h"

typedef struct s_cmd
{
    char    *path;
    char    **args;
    struct s_cmd    *next;
}   t_cmd;

typedef struct s_data
{
    t_cmd   *head_cmd;
    char    **path;
    int     input_file;
    int     output_file;
    int     pipe_fd[2];
    int     _stdin_;
    int     _stdout_;
}   t_data;

void    init(t_data *data);
void    error(char *msg, int status);
void    validate_in_out_files(t_data *data,int ac, char **av);

#endif