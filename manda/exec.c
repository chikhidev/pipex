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

void    free_unused(t_data *data, t_cmd *cmd)
{
    t_cmd   *tmp;

    tmp = data->head_cmd;
    while (tmp)
    {
        if (tmp != cmd && tmp != cmd->prev)
            free_cmd(tmp);
        if (tmp == cmd->prev)
        {
            ft_free(tmp->path);
            free_split(tmp->args);
        }
        tmp = tmp->next;
    }
}

void    execute_cmd(t_data *data, t_cmd *cmd)
{
    if (data->input_file == -1 && cmd->prev == NULL)
        return ft_close(&cmd->entries[1]);
    cmd->child_pid = fork();
    if (cmd->child_pid < 0)
        error(data, "fork failed");
    if (cmd->child_pid == 0)
    {
        ft_close(&cmd->entries[0]);
        manage_fds(data, cmd);
        // free_unused(data, cmd);
        execve(cmd->path, cmd->args, data->env);
        write(2, cmd->args[0], ft_strlen(cmd->args[0]));
        write(2, ": command not found\n", 21);
        exit(data->exit_value);
    }
    else
        ft_close(&cmd->entries[1]);
}

void    wait_for_childs(t_data *data)
{
    t_cmd   *tmp;

    tmp = data->head_cmd;
    while (tmp)
    {
        waitpid(tmp->child_pid, NULL, 0);
        tmp = tmp->next;
    }
}

void    execute_cmds(t_data *data)
{
    t_cmd   *curr_cmd;

    curr_cmd = data->head_cmd;
    while (curr_cmd)
    {
        execute_cmd(data, curr_cmd);
        curr_cmd = curr_cmd->next;
    }
    wait_for_childs(data);
}
