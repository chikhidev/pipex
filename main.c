#include "pipex.h"

int main(int ac, char **av)
{
    t_data data;

    if (ac != 5)
        error("Invalid number of arguments", 1);
    init(&data);
    validate_in_out_files(&data, ac, av);
    return (0);
}