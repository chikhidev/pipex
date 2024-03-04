#include "pipex.h"

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
