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

static void	child_runtime(t_data *data)
{
	data->cmd_options = ft_split(*data->av, ' ');
	data->cmd_path = get_cmd(data->cmd_options[0], data);
	if (data->cmd_path == NULL)
	{
		if (data->cmd_options[0])
			ft_putstr_fd(data->cmd_options[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		if (data->is_last)
			data->exit_status = 127;
	}
	else
	{
		if (execve(data->cmd_path, data->cmd_options, data->envp) == -1)
		{
			free_strs(data->cmd_path, data->cmd_options);
			exit(EXIT_FAILURE);
		}
	}
	free_strs(data->cmd_path, data->cmd_options);
	exit(data->exit_status);
}

static void	first_child(t_data *data)
{
	if (data->is_first)
	{
		if (data->is_heredoc == 0)
		{
			data->fd_in = open(data->filename, O_RDONLY);
			if (data->fd_in == -1)
				exit_error(data->filename, data, 1);
		}
		dup2(data->fd_in, STDIN_FILENO);
		if (data->fd_in != -1)
			close(data->fd_in);
	}
	dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[0]);
	close(data->fd[1]);
	child_runtime(data);
}

static void	last_child(t_data *data)
{
	if (data->is_last)
	{
		if (data->is_bonus)
		{
			data->fd_out = open(data->file_exit, O_CREAT
					| O_WRONLY | O_APPEND, 0644);
			if (data->fd_out == -1)
				exit_error(data->file_exit, data, 1);
		}
		else
		{
			data->fd_out = open(data->file_exit, O_CREAT
					| O_WRONLY | O_TRUNC, 0644);
			if (data->fd_out == -1)
				exit_error(data->file_exit, data, 1);
		}
		dup2(data->fd_out, STDOUT_FILENO);
		close(data->fd_out);
	}
	close(data->fd[0]);
	close(data->fd[1]);
	child_runtime(data);
}

static void	runtime(t_data *data, int i)
{
	pid_t	pid;

	if (i + 2 == data->ac)
		data->is_last = 1;
	if (data->is_first && data->is_last)
	{
		dup2(data->fd_in, STDIN_FILENO);
		if (data->fd_in != -1)
			close(data->fd_in);
	}
	if (pipe(data->fd) == -1)
		exit_error("pipe", data, 0);
	pid = fork();
	if (pid == -1)
		exit_error("fork", data, 0);
	else if (pid == 0 && !data->is_last)
		first_child(data);
	else if (pid == 0)
		last_child(data);
	else
	{
		dup2(data->fd[0], STDIN_FILENO);
		data->is_first = 0;
		close_fds(data);
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
		if (data.fd_in != -1)
			close(data.fd_in);
		if (data.fd_out != -1)
			close(data.fd_out);
	}
	else
		return (ft_putstr_fd(ARG_ERROR, 1), 1);
	return (0);
}
