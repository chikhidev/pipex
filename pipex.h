#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <string.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"

extern char **environ;

typedef struct s_command
{
    char    *cmd_path;
    char    **cmd_args;
    int     pid;
    struct  s_command *next;
}            t_command;

typedef struct s_tacker
{
    int         in_fd;
    int         out_fd;
    int         pipe_fd[2];
    int         is_path_available;
    char        **path;
    t_command   *first_command;
    int         problem;
}               t_tracker;

/*config*/
void    init_tracker(t_tracker *tracker);

void    exit_with_message(char *message, t_tracker *tracker);

/*validation*/
void   validate_in_out_files(char **av, int ac, t_tracker *tracker);
void    check_path_env(t_tracker *tracker);
void    free_split(char **split);
void    execute_commands(t_tracker *tracker);

/*command*/
void   store_commands (char **av, int ac, t_tracker *tracker);


/*v2*/
void    is_executable_command
(t_tracker *tracker, char *cmd, char **cmd_save);

/*exec*/
// void    handle_execution(t_tracker *tracker);

/*memory*/
void    free_all(t_tracker *tracker);

#endif
