/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <abchikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 21:35:19 by abchikhi          #+#    #+#             */
/*   Updated: 2023/11/30 18:07:08 by abchikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/select.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# if BUFFER_SIZE > 2147483646
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

typedef struct s_store
{
	int		bytes;
	int		signal;
	char	*buff;
	char	*temp;
	char	*new_line_pos;
	char	*line;
}			t_store;

char		*get_next_line(int fd, char *limiter);

#endif
