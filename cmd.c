#include "pipex.h"

char    *get_cmd_path(t_data *data, char *cmd)
{
    int i;
    char *tmp;
    char *path;

    i = 0;
    if (data->path_available)
    {
        while (data->path[i])
        {
            tmp = ft_strjoin(data->path[i], "/");
            path = ft_strjoin(tmp, cmd);
            ft_free(tmp);
            if (access(path, F_OK) == 0)
            {
                ft_free(cmd);
                return path;
            }
            ft_free(path);
            i++;
        }
    }
    return cmd;
}

void    create_cmd(t_data *data, char *cmd)
{
    t_cmd   *new;
    t_cmd   *curr;

    new = malloc(sizeof(t_cmd));
    if (!new)
        error(data, "Failed to allocate memory (path)", 1);
    new->args = ft_split(cmd, ' ');
    new->path = get_cmd_path(data, ft_strdup(new->args[0]));
    if (!new->args)
        error(data, "Failed to allocate memory (args)", 1);
    new->next = NULL;
    if (!data->head_cmd)
        data->head_cmd = new;
    else
    {
        curr = data->head_cmd;
        while (curr->next)
            curr = curr->next;
        curr->next = new;
    }
}

void    generate_cmds(t_data *data, char **av)
{
    int i;

    i = 2;
    while (i < 4)
    {
        create_cmd(data, av[i]);
        i++;
    }
}