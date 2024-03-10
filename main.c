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
    launch_pipes(&data);
    execute_cmds(&data);
    free_all(&data);
    return (0);
}