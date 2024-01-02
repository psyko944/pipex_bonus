/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekherbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:33:48 by mekherbo          #+#    #+#             */
/*   Updated: 2023/12/28 23:54:23 by mekherbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
#include <stdlib.h>

static void	child_runtime(t_data *data)
{
	data->cmd_options = ft_split(*data->av, ' ');
	data->cmd_path = get_cmd(data->cmd_options[0], data);
	if (data->cmd_path == NULL)
	{
		if (data->cmd_options[0])
			ft_putstr_fd(data->cmd_options[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		free_strs(NULL, data->cmd_options);
		exit(EXIT_FAILURE);
	}
	else {
		if (execve(data->cmd_path, data->cmd_options, data->envp) == -1)
		{
			ft_putstr_fd("marche pas", 2);
			//free_strs(data->cmd_path, data->cmd_options);
			exit(EXIT_FAILURE);
		}
			
	}
	//exit(EXIT_FAILURE);
	free_strs(data->cmd_path, data->cmd_options);
	exit(0);
}

static void	first_child(t_data *data)
{
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[0]);
	close(data->fd[1]);
	child_runtime(data);
}

static void	last_child(t_data *data)
{
	if (data->is_last)
		dup2(data->fd_out, STDOUT_FILENO);
	if (data->fd_out != -1)
		close(data->fd_out);
	close(data->fd[0]);
	close(data->fd[1]);
	child_runtime(data);
}

static void	runtime(t_data *data, int i)
{
	pid_t	pid;

	if (i + 2 == data->ac)
		data->is_last = 1;
	if (pipe(data->fd) == -1)
		exit_error("pipe", data);
	pid = fork();
	if (pid == -1)
		exit_error("fork", data);
	else if (pid == 0 && !data->is_last)
		first_child(data);
	else if (pid == 0)
		last_child(data);
	else
	{
		wait(NULL);
		dup2(data->fd[0], STDIN_FILENO);
		data->is_first = 0;
		close(data->fd[1]);
		close(data->fd[0]);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;
	int		i;

	if (ac >= 5)
	{
		init_main(&data, ac, av, envp);
		if (!data.is_heredoc)
			i = 2;
		else
			i = 3;
		data.av += 2;
		while (i < ac - 1)
		{
			runtime(&data, i);
			i++;
			data.av++;
		}
	}
	else
	{
		ft_putstr_fd(ARG_ERROR, 1);
		return (1);
	}
	return (0);
}
