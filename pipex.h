#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "libft/libft.h"

extern char **environ;

typedef struct s_cmd
{
    char    *path;
    char    **args;
    int     entries[2];
    struct s_cmd    *next;
    struct s_cmd    *prev;
}   t_cmd;

typedef struct s_data
{
    t_cmd   *head_cmd;
    int     path_available;
    char    **path;
    pid_t   child_pid;
    int     input_file;
    int     output_file;
}   t_data;

void    init(t_data *data);
void    ft_close(int *fd);
void    make_input(t_data *data, int  fd);
void    make_output(t_data *data, int fd);
void    error(t_data *data, char *msg, int status);
void    validate_in_out_files(t_data *data,int ac, char **av);
void    check_path_env(t_data *data);
void    generate_cmds(t_data *data, char **av, int ac);
void    launch_pipe(t_data *data, t_cmd *cmd);
void    execute_cmds(t_data *data);
void    ft_free(void *ptr);
void    free_split(char **split);
void    free_cmd(t_cmd *cmd);
void    free_all(t_data *data);

#endif