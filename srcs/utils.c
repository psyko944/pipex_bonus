/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekherbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:34:28 by mekherbo          #+#    #+#             */
/*   Updated: 2023/12/28 23:46:53 by mekherbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	free_strs(char *str, char **tab)
{
	int	i;

	if (str && *str)
		free(str);
	if (tab && *tab)
	{
		i = -1;
		while (tab[++i])
			free(tab[i]);
		free(tab);
	}
}

void	close_fds(t_data *data)
{
	if (data->fd[0] != -1)
		close(data->fd[0]);
	if (data->fd[1] != -1)
		close(data->fd[1]);
	if (data->is_heredoc)
	{
		if (data->heredoc_fd[0] != -1)
			close(data->heredoc_fd[0]);
		if (data->heredoc_fd[1] != -1)
			close(data->heredoc_fd[1]);
	}
}

void	exit_error(char *msg, t_data *data, int flag)
{
	perror(msg);
	if (data->cmd_options != NULL)
		free_strs(NULL, data->cmd_options);
	if (flag)
		close_fds(data);
	exit(EXIT_FAILURE);
}
