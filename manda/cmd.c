#include "./pipex.h"

void    launch_pipe(t_data *data, t_cmd *cmd)
{
    if (cmd->next)
    {
        if (pipe(cmd->entries) == -1)
            error(data, "Pipe failed");
    }
    else
    {
        cmd->entries[0] = -1;
        cmd->entries[1] = -1;
    }
}

char    *get_cmd_path(t_data *data, char *cmd)
{
    int i;
    char *tmp;
    char *path;

    i = 0;
    if (cmd[0] == '/' || cmd[0] == '.')
        return (cmd);
    else if (data->path)
    {
        while (data->path[i])
        {  
            tmp = ft_strjoin(data->path[i], "/");
            if (!tmp)
                error(data, "Error: str_join failed");
            path = ft_strjoin(tmp, cmd);
            if (!path)
                error(data, "Error: str_join failed");
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
    ft_free(cmd);
    return (NULL);
}

void    create_cmd(t_data *data, char *path, char **args)
{
    t_cmd   *new;
    t_cmd   *curr;

    new = malloc(sizeof(t_cmd));
    if (!new)
        error(data, "Failed to allocate memory (cmd)");
    new->args = args;
    new->path = path;
    new->next = NULL;
    new->child_pid = -1;
    if (!data->head_cmd)
    {
        new->prev = NULL;
        data->head_cmd = new;
        return ;
    }
    curr = data->head_cmd;
    while (curr->next)
        curr = curr->next;
    new->prev = curr;
    curr->next = new;
}

void    generate_cmds(t_data *data, char **av, int ac)
{
    int     i;
    char    *path;
    char    **args;
    t_cmd   *cmd;

    i = 2;
    while (i < (ac - 1))
    {
        args = ft_split(av[i], ' ');
        if (!args)
            error(data, "Failed to allocate memory (args)");
        path = get_cmd_path(data, ft_strdup(args[0]));
        create_cmd(data, path, args);
        i++;
    }
    cmd = data->head_cmd;
    while (cmd)
    {
        launch_pipe(data, cmd);
        cmd = cmd->next;
    }
}
