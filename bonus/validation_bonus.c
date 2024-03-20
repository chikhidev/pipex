#include "./pipex_bonus.h"

void    validate_in_out_files(t_data *data, int ac, char **av)
{
    data->input_file = open(av[1], O_RDONLY);
    if (data->input_file == -1 || access(av[1], R_OK) == -1)
        perror(av[1]);
    if (access(av[ac - 1], F_OK) == -1)
    {
        data->output_file = open(av[ac - 1], O_CREAT | O_WRONLY, 0644);
        if (data->output_file == -1)
            error(data, "Failed to create the file (output file)");
        if (access(av[ac - 1], W_OK) == -1)
            error(data, "Unable to have write permission");
    }
    else
    {
        if (access(av[ac - 1], W_OK) == -1)
            error(data, "Missing write permission (output file)");
        data->output_file = open(av[ac - 1], O_WRONLY | O_TRUNC);
        if (data->output_file == -1)
            error(data, "Invalid output file");
    }
    data->null_fd = open("/dev/null", O_RDONLY);
    if (data->null_fd == -1)
        error(data, "Open failed");
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
