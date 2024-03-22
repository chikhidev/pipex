#include "./pipex.h"

int main(int ac, char **av, char **env)
{
    t_data data;

    init(&data);
    if (ac != 5)
        error(&data, "Invalid number of arguments");
    open_input_file(&data, av);
    data.env = env;
    check_path_env(&data);
    generate_cmds(&data, av, ac);
    execute_cmds(&data, ac, av);
    free_all(&data);
    ft_close(&data.input_file);
    ft_close(&data.output_file);
    if (data.parent_error != 0)
        return (data.parent_error);
    return (data.status >> 8);
}
