#include "./pipex_bonus.h"

void    open_input_file(t_data *data, char **av)
{
    data->input_file = open(av[1], O_RDONLY);
    if (data->input_file == -1 || access(av[1], R_OK) == -1)
        perror(av[1]);
}

void    open_output_file(t_data *data, int ac, char **av)
{
    if (access(av[ac - 1], F_OK) == -1)
    {
        data->output_file = open(av[ac - 1], O_CREAT | O_WRONLY, 0644);
        if (data->output_file == -1)
            error(data, av[ac - 1]);
    }
    else
    {
        data->output_file = open(av[ac - 1], O_WRONLY | O_TRUNC);
        if (data->output_file == -1)
            error(data, av[ac - 1]);
    }
}

void    check_path_env(t_data *data)
{
    int i;
    char *path;

    i = 0;
    while (data->env[i])
    {
        if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
        {
            path = ft_strchr(data->env[i], '/');
            data->path = ft_split(path, ':');
            if (!data->path)
                error(data, "Failed to allocate memory (path)");
            data->path_available = 1;
            return ;
        }
        i++;
    }
}
