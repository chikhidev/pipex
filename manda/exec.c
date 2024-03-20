#include "./pipex.h"

void    manage_io(t_data *data, t_cmd *cmd)
{
    if (cmd->prev == NULL && data->input_file == -1)
        dup2(data->null_fd, STDIN_FILENO);
    else if (cmd->prev)
        dup2(cmd->prev->entries[0], STDIN_FILENO);
    else
        dup2(data->input_file, STDIN_FILENO);
    if (cmd->next)
        dup2(cmd->entries[1], STDOUT_FILENO);
    else
        dup2(data->output_file, STDOUT_FILENO);
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
        execve(cmd->path, cmd->args, data->env);
        write(2, cmd->path, ft_strlen(cmd->path));
        write(2, ": command not found\n", 21);
        free_cmd(cmd);
        free_split(data->path);
        exit(127);
    }
    else
    {
        close(cmd->entries[1]);
        if (cmd->prev)
        	close(cmd->prev->entries[0]);
    }
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
