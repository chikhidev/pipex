#include "./pipex_bonus.h"

void    manage_fds(t_cmd *cmd)
{
    if (cmd->prev)
    {
        dup2(cmd->prev->entries[0], STDIN_FILENO);
        close(cmd->prev->entries[0]);
        close(cmd->prev->entries[1]);
    }
    if (cmd->next)
    {
        dup2(cmd->entries[1], STDOUT_FILENO);
        close(cmd->entries[0]);
        close(cmd->entries[1]);
    }
}

void execute_cmd(t_data *data, t_cmd *cmd) {
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        manage_fds(cmd);
        execve(cmd->path, cmd->args, data->env);
        perror(cmd->path);
        free_all(data);
        exit(1);
    }
    else
    {
        if (cmd->prev) {
            close(cmd->prev->entries[0]);
            close(cmd->prev->entries[1]);
        }
        if (cmd->next) {
            close(cmd->entries[0]);
            close(cmd->entries[1]);
        }
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
