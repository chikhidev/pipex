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

typedef struct s_tacker
{
    int     in_fd;
    int     out_fd;
    int     is_path_available;
    char    **path;
    int     child_pid;
    char    *cmd1_path;
    char    *cmd2_path;
}               t_tracker;

/*config*/
void    init_tracker(t_tracker *tracker);
void    exit_with_message(char *message, t_tracker *tracker);

/*validation*/
void	validate_args(t_tracker *tracker, int ac, char **av);
void    free_commands(char **cmd);
void	check_path_env(char **env, t_tracker *tracker);

/*v2*/
void    is_executable_command
(t_tracker *tracker, char *cmd, char *cmd_save);

#endif
