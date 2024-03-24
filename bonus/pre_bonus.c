/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <abchikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:46:45 by abchikhi          #+#    #+#             */
/*   Updated: 2024/03/24 19:46:46 by abchikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exit_error(t_data *data, t_cmd *cmd, char *msg, int status)
{
	write(2, cmd->args[0], ft_strlen(cmd->args[0]));
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	free_cmd(cmd);
	free_split(data->path);
	exit(status);
}

void	pre_execution(t_data *data, t_cmd *cmd)
{
	if (!cmd->path || !cmd->args || !cmd->args[0])
		exit_error(data, cmd, ": command not found", 127);
	else
	{
		if (access(cmd->path, F_OK) == -1)
			exit_error(data, cmd, ": no such file or directory", 127);
		else if (access(cmd->path, X_OK) == -1)
			exit_error(data, cmd, ": permission denied", 126);
	}
}
