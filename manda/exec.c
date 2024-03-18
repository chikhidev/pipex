#include "./pipex.h"

void    manage_fds(t_data *data, t_cmd *cmd)
{
    if (cmd->prev)
        make_input(data, cmd->prev->entries[0]);
    else
        make_input(data, data->input_file);
    if (cmd->next)
        make_output(data, cmd->entries[1]);
    else
        make_output(data, data->output_file);
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
        execve(cmd->path, cmd->args, data->env);
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
