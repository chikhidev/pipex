#include "pipex.h"

void    validate_in_out_files(t_data *data, int ac, char **av)
{
    if (access(av[1], F_OK) == -1)
        error("Input file does not exist", 1);
    if (access(av[1], R_OK) == -1)
        error("Missing read permission", 1);
    data->input_file = open(av[1], O_RDONLY);
    if (data->input_file == -1 || access(av[1], R_OK) == -1)
        error("Invalid input file", 1);
    if (access(av[ac - 1], F_OK) == -1)
    {
        data->output_file = open(av[ac - 1], O_CREAT | O_WRONLY);
        if (data->output_file == -1)
            error("Failed to create the file", 1);
    }
    else
    {
        if (access(av[ac - 1], W_OK) == -1)
            error("Missing write permission", 1);
        data->output_file = open(av[ac - 1], O_WRONLY | O_TRUNC);
        if (data->output_file == -1)
            error("Invalid output file", 1);
    }
}
