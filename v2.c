#include "pipex.h"

void validate_existness_of_command
(t_tracker *tracker, char *cmd, char *cmd_path, char **save)
{
    int found;
    int i;
    char *_dir_;
    
    found = 0;
    i = 0;
    while (tracker->path[i] && !found)
    {
        _dir_ = ft_strjoin(tracker->path[i], "/");
        cmd_path = ft_strjoin(_dir_, cmd);
        free(_dir_);
        if (access(cmd_path, X_OK) == 0)
        {
            *save = cmd_path;
            found = 1;
        }
        free(cmd_path);
        i++;
    }
    if (!found)
    {
        ft_printf("%s not found\n", cmd);
        exit_with_message("Command not found\n", tracker);
    }
}

void    is_executable_command
(t_tracker *tracker, char *cmd, char *cmd_save)
{
    char *cmd_path;

    cmd_path = NULL;
    if (cmd[0] == '/')
    {
        cmd_path = ft_strdup(cmd);
        if (access(cmd_path, X_OK) == 0)
            tracker->cmd1_path = cmd_path;
        else
        {
            free(cmd_path);
            ft_printf("%s not found\n", cmd);
            exit_with_message("Command not found\n", tracker);
        }
    }
    else if (tracker->is_path_available)
        validate_existness_of_command(tracker,
            cmd, cmd_path,
            &cmd_save);
    else
    {
        ft_printf("`%s` not found\n", cmd);
        exit_with_message("Command not found\n", tracker);
    }
}
