/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekherbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:34:15 by mekherbo          #+#    #+#             */
/*   Updated: 2023/12/27 18:34:18 by mekherbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

static void	clean_struct(t_data *data)
{
	data->envp = NULL;
	data->av = NULL;
	data->ac = -1;
	data->fd_in = -1;
	data->fd_out = -1;
	data->is_last = 0;
	data->is_first = 0;
	data->cmd_path = NULL;
	data->cmd_options = NULL;
}

static void	runtime_heredoc(t_data *data)
{
	char	*line;
	size_t	delimiter_len;

	delimiter_len = ft_strlen(data->delimiter);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line)
			exit(0);
		if (ft_strncmp(line, data->delimiter, delimiter_len) == 0
			&& line[delimiter_len] == '\n')
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, data->heredoc_fd[1]);
		free(line);
	}
}

static void	init_heredoc(t_data *data)
{
	data->delimiter = data->av[2];
	if (pipe(data->heredoc_fd) == -1)
		exit_error("pipe", data);
	runtime_heredoc(data);
	if (data->is_bonus)
	{
		data->fd_out = open(data->av[data->ac - 1], O_CREAT
				| O_WRONLY | O_APPEND, 0644);
		if (data->fd_out == -1)
			exit(EXIT_FAILURE);
	}
	else
	{
		data->fd_out = open(data->av[data->ac - 1], O_CREAT
				| O_WRONLY | O_TRUNC, 0644);
		if (data->fd_out == -1)
			exit(EXIT_FAILURE);
	}
	data->fd_in = data->heredoc_fd[0];
	if (data->fd_in == -1)
		exit(EXIT_FAILURE);
	close(data->heredoc_fd[1]);
	data->av++;
}

static void	init_struct(t_data *data, int ac, char **av, char**envp)
{
	clean_struct(data);
	data->ac = ac;
	data->av = av;
	data->envp = envp;
	data->is_first = 1;
	if (data->is_heredoc)
		init_heredoc(data);
	else
	{
		data->fd_in = open(av[1], O_RDONLY);
		if (data->fd_in == -1)
			exit_error(av[1], data);
		data->fd_out = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (data->fd_out == -1)
			exit_error(av[ac - 1], data);
	}
}

void	init_main(t_data *data, int ac, char **av, char **envp)
{
	data->is_heredoc = 0;
	data->is_bonus = 0;
	if (ft_strnstr(av[0], "bonus", ft_strlen(av[0])))
		data->is_bonus = 1;
	if (!ft_strncmp(av[1], "here_doc", ft_strlen(av[1]))
		&& data->is_bonus && ac > 1)
		data->is_heredoc = 1;
	init_struct(data, ac, av, envp);
	dup2(data->fd_in, STDIN_FILENO);
	if (data->fd_in != -1)
		close(data->fd_in);
}
