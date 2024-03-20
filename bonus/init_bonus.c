#include "./pipex_bonus.h"

void    make_input(t_data *data, int  fd)
{
    if (fd == -1)
        return ;
    if (dup2(fd, STDIN_FILENO) == - 1)
        error(data, "dup2 failed");
}

void    make_output(t_data *data, int fd)
{
    if (fd == -1)
        return ;
    if (dup2(fd, STDOUT_FILENO) == -1)
        error(data, "dup2 failed");
}

void    init(t_data *data)
{
    data->head_cmd = NULL;
    data->path = NULL;
    data->input_file = -1;
    data->output_file = -1;
    data->child_pid = -1;
}
