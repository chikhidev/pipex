/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abchikhi <abchikhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 02:27:09 by abchikhi          #+#    #+#             */
/*   Updated: 2024/01/29 16:36:41 by abchikhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int ac, char **av)
{
    t_tracker   tracker;
    
    init_tracker(&tracker);
    validate_args(&tracker, ac, av);
    check_path_env(environ, &tracker);
    is_executable_command(&tracker, tracker.cmd1[0], &tracker.cmd1_path);
    is_executable_command(&tracker, tracker.cmd2[0], &tracker.cmd2_path);
    handle_execution(&tracker);
    /*check memo leaks*/
    // system("valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes ./pipex");
    return (0);
}