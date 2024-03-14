#include "pipex.h"

int main(int ac, char **av)
{
    t_data data;

    init(&data);
    // if (ac != 5)
    //     error(&data, "Invalid number of arguments", 1);
    validate_in_out_files(&data, ac, av);
    check_path_env(&data);
    generate_cmds(&data, av, ac);

    printf("input: %d\n", data.input_file);
    printf("output: %d\n", data.output_file);
    execute_cmds(&data);
    while (wait(NULL) > 0);
    free_all(&data);
    ft_close(&data.input_file);
    ft_close(&data.output_file);
    return (0);
}
