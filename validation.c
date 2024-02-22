/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <abchikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 02:27:06 by abchikhi          #+#    #+#             */
/*   Updated: 2024/02/10 14:03:22 by abchikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*check if path env exists*/
void	check_path_env(char **env, t_tracker *tracker)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 4) == 0)
		{
			tracker->is_path_available = 1;
			tracker->path = ft_split(env[i] + 5, ':');
			if (!tracker->path)
				exit_with_message("Failed to split path env", tracker);
			if (tracker->path[0] == NULL)
				exit_with_message("Failed to split path env", tracker);
			break ;
		}
		i++;
	}
}

void	validate_commands(t_tracker *tracker, char *cmd1, char *cmd2)
{
	char	**cmd1_args;
	char	**cmd2_args;

	(void)tracker;
	cmd1_args = ft_split(cmd1, ' ');
	if (!cmd1_args)
		exit_with_message("First command is not valid", tracker);
	if (cmd1_args[0] == NULL)
		exit_with_message("First command is not valid", tracker);
	free_commands(cmd1_args);
	cmd2_args = ft_split(cmd2, ' ');
	if (!cmd2_args)
		exit_with_message("Second command is valid", tracker);
	if (cmd2_args[0] == NULL)
		exit_with_message("Second command is valid", tracker);
	free_commands(cmd2_args);
	check_path_env(environ, tracker);
}

void	validate_args(t_tracker *tracker, int ac, char **av)
{
	int		fd;
	
	if (ac != 5)
		exit_with_message("Invalid number of arguments", tracker);
	/*validate first file*/
	if (access(av[1], F_OK) == -1)
		exit_with_message("Input file does not exist", tracker);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		exit_with_message("Failed to open input file", tracker);
	close(fd);
	/*validate second file*/
	if (access(av[4], F_OK) == -1)
		exit_with_message("Output file does not exist", tracker);
	fd = open(av[4], O_WRONLY);
	if (fd == -1)
		exit_with_message("Failed to open output file", tracker);
	close(fd);
	/*validate commands*/
	validate_commands(tracker, av[2], av[3]);
}
