#include "pipex.h"

void validate_existness_of_command
(t_tracker *tracker, char *cmd, char **cmd_save)
{
    int found;
    int i;
    char *_dir_;
    
    found = 0;
    i = 0;
    while (tracker->path[i])
    {
        _dir_ = ft_strjoin(tracker->path[i], "/");
        *cmd_save = ft_strjoin(_dir_, cmd);
        free(_dir_);
        if (access(*cmd_save, X_OK) == 0)
        {
            found = 1;
            break ;
        }
        free(*cmd_save);
        i++;
    }
    if (!found)
    {
        *cmd_save = NULL;
        ft_printf("%s not found\n", cmd);
        exit_with_message("Command not found\n", tracker);
    }
}

void    is_executable_command
(t_tracker *tracker, char *cmd, char **cmd_save)
{
    if (cmd[0] == '/')
    {
        if (access(cmd, X_OK) != 0)
        {
            ft_printf("%s not found\n", cmd);
            exit_with_message("Command not found\n", tracker);
        }
        else
            *cmd_save = cmd;
    }
    else if (tracker->is_path_available)
        validate_existness_of_command(tracker,
            cmd, cmd_save);
    else
    {
        ft_printf("`%s` not found\n", cmd);
        exit_with_message("Command not found\n", tracker);
    }
}
