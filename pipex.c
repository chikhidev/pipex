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
    // t_command	*cmd;

    if (ac != 5)
        exit_with_message("Invalid number of arguments", &tracker);
    init_tracker(&tracker);
    validate_in_out_files(av, ac, &tracker);
    check_path_env(&tracker);
    store_commands(av, ac, &tracker);


    t_command *cmd;
    cmd = tracker.first_command;
    while (cmd)
    {
        ft_printf("cmd_path: %s\n", cmd->cmd_path);
        ft_printf("cmd_args: \n");
        for (int i = 0; cmd->cmd_args[i]; i++)
            ft_printf("\t%s\n", cmd->cmd_args[i]);
        ft_printf("\n\n-------------------\n");
        cmd = cmd->next;
    }

    return (0);
}