#include "./pipex_bonus.h"

void    serve_normal_behav(t_data *data, char **av, int ac, char **env)
{
    open_input_file(data, av);
    data->env = env;
    check_path_env(data);
    generate_cmds(data, av, ac, 2);
    execute_cmds(data,ac, av);
    free_all(data);
    ft_close(&data->input_file);
    ft_close(&data->output_file);
}

void    get_input(t_data *data)
{
    char *line;

    line = get_next_line(STDIN_FILENO, data->limiter);
    while (line)
    {
        if (ft_strncmp(line, data->limiter, ft_strlen(data->limiter)) == 0 &&
            ft_strlen(data->limiter) == (ft_strlen(line) - 1))
            return ft_free(line);
        write(data->input_file, line, ft_strlen(line));
        ft_free(line);
        line = get_next_line(STDIN_FILENO, data->limiter);
    }
    ft_free(line);
}

int main(int ac, char **av, char **env)
{
    t_data data;

    init(&data);
    if (ac >= 5 && ft_strncmp(av[1], "here_doc", 9) == 0)
    {
        printf("here_doc is called\n");
        data.limiter = av[2];
        if (pipe(data.here_doc_pipe) == -1)
            error(&data, "Pipe failed");
        data.input_file = data.here_doc_pipe[0];
        data.output_file = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        data.env = env;
        check_path_env(&data);
        generate_cmds(&data, av, ac, 3);
        get_input(&data);
        execute_cmds(&data, ac, av);
        ft_close(&data.here_doc_pipe[1]);
        ft_close(&data.here_doc_pipe[0]);
        free_all(&data);
    }
    else if (ac >= 5)
        serve_normal_behav(&data, av, ac, env);
    else
        error(&data, "Invalid number of arguments");
    return (0);
}
