#include "pipex.h"

//./pipex Makfile cat cat outFile

void    manage_fds(t_data *data, t_cmd *cmd)
{
    write(2, "inside path: ", 14);
    write(2, cmd->path, ft_strlen(cmd->path));
    write(2, "\n", 1);

    if (cmd->prev)
        make_input(data, cmd->prev->entries[0]);
    else
        make_input(data, data->input_file);
    if (cmd->next)
        make_output(data, cmd->entries[1]);
    else
        make_output(data, data->output_file);
}

void    close_unused_fds(t_data *data)
{
    t_cmd *tmp;

    tmp = data->head_cmd;
    while (tmp)
    {
        ft_close(&tmp->entries[0]);
        ft_close(&tmp->entries[1]);
        tmp = tmp->next;
    }
}

void    execute_cmd(t_data *data, t_cmd *cmd)
{
    pid_t   pid;

    pid = fork();
    if (pid < 0)
        error(data, "fork failed", 1);
    if (pid == 0)
    {
        ft_close(&cmd->entries[0]);
        manage_fds(data, cmd);
        execve(cmd->path, cmd->args, environ);
        perror(cmd->path);
        exit(1);
    }
    else
        ft_close(&cmd->entries[1]);
}

void    execute_cmds(t_data *data)
{
    t_cmd   *curr_cmd;
    int     cmd_index;

    cmd_index = 0;
    curr_cmd = data->head_cmd;

    while (curr_cmd)
    {
        launch_pipe(data, curr_cmd);
        execute_cmd(data, curr_cmd);
        if (curr_cmd->prev && curr_cmd->prev->prev)
        {
            ft_close(&curr_cmd->prev->prev->entries[0]);
            ft_close(&curr_cmd->prev->prev->entries[1]);
        }

        curr_cmd = curr_cmd->next;
        cmd_index += 1;
    }
}

// void    execute_cmds(t_data *data)
// {
//     t_cmd   *curr_cmd;
//     int     cmd_index;

//     cmd_index = 0;
//     curr_cmd = data->head_cmd;

//     while (curr_cmd)
//     {
//         launch_pipe(data, curr_cmd);
//         if (curr_cmd->prev && curr_cmd->prev->prev)
//         {
//             // write(2, "closing ", 9);
//             // write(2, ft_itoa(curr_cmd->prev->prev->entries[0]), ft_strlen(ft_itoa(curr_cmd->prev->prev->entries[0])));
//             // write(2, "\n", 1);
//             // write(2, "closing ", 9);
//             // write(2, ft_itoa(curr_cmd->prev->prev->entries[1]), ft_strlen(ft_itoa(curr_cmd->prev->prev->entries[1])));
//             // write(2, "\n", 1);
//             ft_close(&curr_cmd->prev->prev->entries[0]);
//             ft_close(&curr_cmd->prev->prev->entries[1]);
//         }
//         manage_fds(data, curr_cmd);
//         execute_cmd(data, curr_cmd);
//         curr_cmd = curr_cmd->next;
//         cmd_index += 1;
//     }
// }
