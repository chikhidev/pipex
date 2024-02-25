#include "pipex.h"

void    check_path_env(t_tracker *tracker)
{
    int i;
    char *path;

    i = 0;
    while (environ[i])
    {
        if (ft_strncmp(environ[i], "PATH=", 5) == 0)
        {
            path = ft_strchr(environ[i], '/');
            tracker->path = ft_split(path, ':');
            if (!tracker->path)
                exit_with_message("unable to split path env", tracker);
            tracker->is_path_available = 1;
            return ;
        }
        i++;
    }
}

void validate_existness_of_command
(t_tracker *tracker, char *cmd, char **cmd_save, int *found)
{
    int i;
    char *_dir_;
    
    i = 0;
    while (tracker->path[i])
    {
        _dir_ = ft_strjoin(tracker->path[i], "/");
        *cmd_save = ft_strjoin(_dir_, cmd);
        free(_dir_);
        if (access(*cmd_save, X_OK) == 0)
        {
            *found = 1;
            break ;
        }
        free(*cmd_save);
        i++;
    }
}

void    is_executable_command
(t_tracker *tracker, char *cmd, char **cmd_save)
{
    int found;

    found = 0;
    if (tracker->is_path_available)
        validate_existness_of_command(tracker,
            cmd, cmd_save, &found);
    if (!found)
    {
        if (access(cmd, F_OK) != 0)
        {
            ft_printf("%s not found\n", cmd);
            *cmd_save = NULL;
            exit_with_message("Command not found\n", tracker);
        }
        else if (access(cmd, X_OK) != 0)
        {
            *cmd_save = NULL;
            exit_with_message("No permession to execute this command.\n", tracker);
        }
        else
        {
            *cmd_save = cmd;
            return ;
        }
        *cmd_save = NULL;
        ft_printf("%s not found\n", *cmd);
        exit_with_message(NULL, tracker);
    }
}
