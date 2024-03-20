#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"

typedef struct s_cmd
{
    char    *path;
    char    **args;
    int     entries[2];
    pid_t   child_pid;
    struct s_cmd    *next;
    struct s_cmd    *prev;
}   t_cmd;

typedef struct s_data
{
    char    **env;
    t_cmd   *head_cmd;
    int     path_available;
    char    **path;
    char    *limiter;
    int     here_doc_pipe[2];
    pid_t   child_pid;
    int     input_file;
    int     output_file;
    int     null_fd;
}   t_data;

void    init(t_data *data);
void    ft_close(int *fd);
void    make_input(t_data *data, int  fd);
void    make_output(t_data *data, int fd);
void    error(t_data *data, char *msg);
void    validate_in_out_files(t_data *data,int ac, char **av);
void    check_path_env(t_data *data);
void    generate_cmds(t_data *data, char **av, int ac, int start);
void    launch_pipe(t_data *data, t_cmd *cmd);
void    execute_cmds(t_data *data);
void    ft_free(void *ptr);
void    free_split(char **split);
void    free_cmd(t_cmd *cmd);
void    free_cmds(t_data *data, t_cmd *exception);
void    free_all(t_data *data);

#endif