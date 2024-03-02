#include "pipex.h"

int main(int ac, char **av)
{
    t_data data;

    init(&data);
    if (ac != 5)
        error(&data, "Invalid number of arguments", 1);
    validate_in_out_files(&data, ac, av);
    return (0);
}