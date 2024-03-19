#include "./pipex.h"

int main(int ac, char **av, char **env)
{
    t_data data;

    init(&data);
    if (ac != 5)
        error(&data, "Invalid number of arguments");
    validate_in_out_files(&data, ac, av);
    data.env = env;
    check_path_env(&data);
    generate_cmds(&data, av, ac);
    execute_cmds(&data);
    free_all(&data);
    ft_close(&data.input_file);
    ft_close(&data.output_file);
    return (data.exit_value);
}
