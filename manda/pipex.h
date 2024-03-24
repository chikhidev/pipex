/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <abchikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:47:12 by abchikhi          #+#    #+#             */
/*   Updated: 2024/03/24 19:47:13 by abchikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_cmd
{
	char			*path;
	char			**args;
	int				entries[2];
	pid_t			child_pid;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_data
{
	char			**env;
	t_cmd			*head_cmd;
	char			**path;
	int				status;
	int				input_file;
	int				output_file;
	int				parent_error;
}					t_data;

void				init(t_data *data);
void				ft_close(int *fd);
void				make_input(t_data *data, int fd);
void				make_output(t_data *data, int fd);
void				error(t_data *data, char *msg);
void				open_input_file(t_data *data, char **av);
void				open_output_file(t_data *data, int ac, char **av);
void				check_path_env(t_data *data);
void				generate_cmds(t_data *data, char **av, int ac);
void				launch_pipe(t_data *data, t_cmd *cmd);
void				pre_execution(t_data *data, t_cmd *cmd);
void				execute_cmds(t_data *data, int ac, char **av);
void				ft_free(void *ptr);
void				free_split(char **split);
void				free_cmd(t_cmd *cmd);
void				free_cmds(t_data *data, t_cmd *exception);
void				free_all(t_data *data);

#endif