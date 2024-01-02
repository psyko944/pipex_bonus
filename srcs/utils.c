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

static void	close_fds(t_data *data)
{
	if (data->fd_in != -1)
		close(data->fd_in);
	if (data->fd_out != -1)
		close(data->fd_out);
}

void	exit_error(char *msg, t_data *data)
{
	perror(msg);
	if (data->cmd_options != NULL)
		free_strs(NULL, data->cmd_options);
	close_fds(data);
	exit(EXIT_FAILURE);
}
