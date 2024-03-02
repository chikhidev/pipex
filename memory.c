#include "pipex.h"

void    free_split(char **split)
{
    int i;

    i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

void    free_cmds(t_data *data)
{
    t_cmd   *tmp;
    t_cmd   *curr;

    curr = data->head_cmd;
    while (curr)
    {
        tmp = curr->next;
        free_split(curr->args);
        free(curr->path);
        curr = tmp;
    }
}

void    free_all(t_data *data)
{
    if (data->path)
        free_split(data->path);
    free_cmds(data);
}