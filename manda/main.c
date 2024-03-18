#include "./pipex.h"

int main(int ac, char **av, char **env)
{
    t_data data;

    init(&data);
    if (ac != 5)
        error(&data, "Invalid number of arguments", 1);
    validate_in_out_files(&data, ac, av);
    data.env = env;
    check_path_env(&data);
    generate_cmds(&data, av, ac);


    // for (t_cmd *tmp = data.head_cmd; tmp;  tmp = tmp->next) {
    //     printf("cmd path: %s\n",  tmp->path);
    //     for (int i = 0; tmp->args[i]; i++)
    //         printf( "arg[%d]: %s\n", i, tmp->args[i]);
    //     printf("pipe: [%d, %d]\n", tmp->entries[0],  tmp->entries[1]);
    // }
    // return 0;

    execute_cmds(&data);
    while (wait(NULL) > 0);
    free_all(&data);
    ft_close(&data.input_file);
    ft_close(&data.output_file);
    return (0);
}
