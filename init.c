#include "pipex.h"

void    make_input(t_data *data, int  fd)
{
    char *str;

    if (fd == -1)
        return ;
    if (dup2(fd, STDIN_FILENO) == - 1)
        error(data, "dup2 failed", 1);
    str = ft_itoa(fd);
    write(2, str, ft_strlen(str));//debug
    write(2, " is the input file\n", 20);//debug
    ft_free(str);
}

void    make_output(t_data *data, int fd)
{
    char *str;
    if (fd == -1)
        return ;
    if (dup2(fd, STDOUT_FILENO) == -1)
        error(data, "dup2 failed", 1);
    str = ft_itoa(fd);
    write(2, str, ft_strlen(str));//debug
    write(2, " is the output file\n", 20);//debug
    ft_free(str);
}

void    init(t_data *data)
{
    data->head_cmd = NULL;
    data->path = NULL;
    data->input_file = -1;
    data->output_file = -1;
    data->child_pid = -1;
}
