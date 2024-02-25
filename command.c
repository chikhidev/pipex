#include "pipex.h"

//./pipex file1 "ls" "wc -l" file2

char    *get_cmd_path(char *cmd, t_tracker *tracker)
{
    char    *path;
    char    *tmp;
    int     i;

    i = 0;
    if (tracker->is_path_available)
    {
        while (tracker->path[i])
        {
            tmp = ft_strjoin(tracker->path[i], "/");
            path = ft_strjoin(tmp, cmd);
            free(tmp);
            if (access(path, F_OK) == 0)
                return (path);
            free(path);
            i++;
        }
    }
    if (access(cmd, F_OK) == 0)
        return (cmd);
    return (NULL);
}

t_command   *create_command (char *cmd, t_tracker *tracker)
{
    t_command   *command;

    command = malloc(sizeof(t_command));
    command->cmd_path = get_cmd_path(cmd, tracker);
    command->cmd_args = ft_split(cmd, ' ');
    command->next = NULL;
    return (command);
}

void    push_command(t_command *cmd, t_tracker *tracker)
{
    t_command   *tmp;

    if (tracker->first_command == NULL)
        tracker->first_command = cmd;
    else
    {
        tmp = tracker->first_command;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = cmd;
    }
}

void    store_commands (char **av, int ac, t_tracker *tracker)
{
    t_command   *cmd;
    int         i;

    i = 0;
    while (i < (ac - 2))
    {
        cmd = create_command(av[i + 2], tracker);
        push_command(cmd, tracker);
        i++;
    }
}

//ac = 5
//