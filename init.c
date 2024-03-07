#include "pipex.h"

void    make_input(int  fd)
{
    if (fd == -1)
        return ;
    dup2(fd, STDIN_FILENO);
    write(2, "input made\n", 12);//debug
}

void    make_output(int fd)
{
    if (fd == -1)
        return ;
    dup2(fd, STDOUT_FILENO);
    write(2, "output made\n", 13);//debug
}

void    init(t_data *data)
{
    data->head_cmd = NULL;
    data->path = NULL;
    data->input_file = -1;
    data->output_file = -1;
    data->child_pid = -1;
}
