/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekherbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:34:03 by mekherbo          #+#    #+#             */
/*   Updated: 2023/12/28 23:45:27 by mekherbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

static char	**get_paths(char **envp)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	i = -1;
	while (envp[++i])
	{
		path = ft_strnstr(envp[i], "PATH=", 5);
		if (path)
		{
			path = path + 5;
			break ;
		}
	}
	paths = ft_split(path, ':');
	i = -1;
	while (paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
	}
	return (paths);
}

char	*get_cmd_path(char **paths, char *cmd)
{
	int		i;
	char	*cmd_path;

	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
		{
			free_strs(NULL, paths);
			exit(EXIT_FAILURE);
		}
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}

char	*get_cmd(char *cmd, t_data *data)
{
	char	**paths;
	char	*cmd_path;
	int		i;

	i = 0;
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	paths = get_paths(data->envp);
	cmd_path = get_cmd_path(paths, cmd);
	if (!cmd_path)
		return (NULL);
	free_strs(NULL, paths);
	return (cmd_path);
}
