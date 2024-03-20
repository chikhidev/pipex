#include "./pipex_bonus.h"

void    ft_free(void    *ptr)
{
    if (ptr)
    {
        free(ptr);
        ptr = NULL;
    }
}

void    free_split(char **split)
{
    int i;

    i = 0;
    while (split[i])
    {
        ft_free(split[i]);
        i++;
    }
    ft_free(split);
}

void    free_cmd(t_cmd *cmd)
{
    ft_free(cmd->path);
    free_split(cmd->args);
    ft_close(&cmd->entries[0]);
    ft_close(&cmd->entries[1]);
    ft_free(cmd);
}

void    free_cmds(t_data *data, t_cmd *exception)
{
    t_cmd   *tmp;
    t_cmd   *curr;

    curr = data->head_cmd;
    while (curr)
    {
        tmp = curr->next;
        if (curr != exception)
            free_cmd(curr);
        curr = tmp;
    }
}

void    free_all(t_data *data)
{
    if (data->path)
        free_split(data->path);
    free_cmds(data, NULL);
}