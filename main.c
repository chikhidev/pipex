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
    execute_cmds(&data);

    // int i = 0;
    // t_cmd *tmp = data.head_cmd;
    // while (tmp)
    // {
    //     printf("cmd[%d]: %s\n", i, tmp->path);
    //     printf("args:\n");
    //     int j = 0;
    //     while (tmp->args[j])
    //     {
    //         printf("\t%s\n", tmp->args[j]);
    //         j++;
    //     }
    //     i++;
    //     tmp = tmp->next;
    // }

    free_all(&data);
    return (0);
}