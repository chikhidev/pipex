#include "./pipex.h"

void    manage_io(t_data *data, t_cmd *cmd)
{
    if (cmd->prev == NULL && data->input_file == -1)
    {
        free_all(data);
        exit(1);
    }
    else if (cmd->prev)
        dup2(cmd->prev->entries[0], STDIN_FILENO);
    else
        dup2(data->input_file, STDIN_FILENO);
    if (cmd->next)
        dup2(cmd->entries[1], STDOUT_FILENO);
    else
        dup2(data->output_file, STDOUT_FILENO);
    ft_close(&data->input_file);
    ft_close(&data->output_file);
}

void    execute_cmd(t_data *data, t_cmd *cmd)
{
    cmd->child_pid = fork();
    if (cmd->child_pid == -1)
        error(data, "Fork failed");
    if (cmd->child_pid == 0)
    {
        manage_io(data, cmd);
        free_cmds(data, cmd);
        ft_close(&cmd->entries[0]);
        ft_close(&cmd->entries[1]);
        pre_execution(data, cmd);
        execve(cmd->path, cmd->args, data->env);
        write(2, cmd->args[0], ft_strlen(cmd->args[0]));
        write(2, "execve failed\n", 15);
        write(2, "\n", 1);
        free_cmd(cmd);
        free_split(data->path);
        exit(1);
    }
    else
    {
        ft_close(&cmd->entries[1]);
        if (cmd->prev)
        	ft_close(&cmd->prev->entries[0]);
    }
}

void    wait_for_childs(t_data *data)
{
    t_cmd   *tmp;

    tmp = data->head_cmd;
    while (tmp)
    {
        if (tmp->child_pid != -1)
            waitpid(tmp->child_pid, &data->status, 0);
        tmp = tmp->next;
    }
}

void    execute_cmds(t_data *data, int ac, char **av)
{
    t_cmd   *curr_cmd;

    curr_cmd = data->head_cmd;
    while (curr_cmd)
    {
        if (!curr_cmd->next)
            open_output_file(data, ac, av);
        if (data->parent_error == 0)
            execute_cmd(data, curr_cmd);
        if (curr_cmd->prev)
        {
            ft_close(&curr_cmd->prev->entries[0]);
            ft_close(&curr_cmd->prev->entries[1]);
        }
        curr_cmd = curr_cmd->next;
    }
    wait_for_childs(data);
}
