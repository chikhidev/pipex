/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <abchikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:46:32 by abchikhi          #+#    #+#             */
/*   Updated: 2024/03/24 19:46:33 by abchikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

void	serve_normal_behav(t_data *data, char **av, int ac, char **env)
{
	open_input_file(data, av);
	data->env = env;
	check_path_env(data);
	generate_cmds(data, av, ac, 2);
	execute_cmds(data, ac, av);
	free_all(data);
	ft_close(&data->input_file);
	ft_close(&data->output_file);
}

void	get_input(t_data *data)
{
	char	*line;

	write(1, "> ", 2);
	line = get_next_line(STDIN_FILENO, data->limiter);
	while (line)
	{
		if (ft_strncmp(line, data->limiter, ft_strlen(data->limiter)) == 0
			&& ft_strlen(data->limiter) == (ft_strlen(line) - 1))
			return (ft_free(line));
		write(data->here_doc_pipe[1], line, ft_strlen(line));
		ft_free(line);
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO, data->limiter);
	}
	ft_free(line);
}

void	serve_here_doc(t_data *data, char **av, int ac, char **env)
{
	data->limiter = av[2];
	if (pipe(data->here_doc_pipe) == -1)
		error(data, "Pipe failed");
	data->env = env;
	check_path_env(data);
	generate_cmds(data, av, ac, 3);
	get_input(data);
	data->input_file = data->here_doc_pipe[0];
	ft_close(&data->here_doc_pipe[1]);
	execute_cmds(data, ac, av);
	free_all(data);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	init(&data);
	if (ac >= 2 && ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		if (ac >= 5)
			serve_here_doc(&data, av, ac, env);
		else
			error(&data, "Invalid number of arguments");
	}
	else if (ac >= 5)
		serve_normal_behav(&data, av, ac, env);
	else
		error(&data, "Invalid number of arguments");
	if (data.parent_error != 0)
		return (data.parent_error);
	return (data.status >> 8);
}
