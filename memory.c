#include "pipex.h"

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

void    free_cmds(t_data *data)
{
    t_cmd   *tmp;
    t_cmd   *curr;

    curr = data->head_cmd;
    while (curr)
    {
        tmp = curr->next;
        if (curr->args)
            free_split(curr->args);
        if (curr->path)
            ft_free(curr->path);
        ft_free(curr);
        curr = tmp;
    }
}

void    free_all(t_data *data)
{
    if (data->path)
        free_split(data->path);
    free_cmds(data);
}