#include "pipex.h"

void    make_input(int  fd)
{
    if (fd != -1)
        dup2(fd, STDIN_FILENO);
}

void    make_output(int fd)
{
    if (fd != -1)
        dup2(fd, STDOUT_FILENO);
}

void    init(t_data *data)
{
    data->head_cmd = NULL;
    data->path = NULL;
    data->input_file = -1;
    data->output_file = -1;
    data->pipe[0] = -1;
    data->pipe[1] = -1;
    data->child_pid = -1;
}
