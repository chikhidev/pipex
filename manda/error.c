/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <abchikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:47:00 by abchikhi          #+#    #+#             */
/*   Updated: 2024/03/24 19:47:01 by abchikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void	ft_close(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

void	error(t_data *data, char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "/n", 1);
	free_all(data);
	if (data->status >> 8 == 0)
		exit(1);
	exit(data->status >> 8);
}
