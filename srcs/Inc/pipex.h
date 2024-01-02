/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekherbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 18:35:04 by mekherbo          #+#    #+#             */
/*   Updated: 2023/12/28 23:43:31 by mekherbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H
/*        libraries     */

# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include "../libft/libft.h"

# define ARG_ERROR "too few arguments\n./pipex file1 cmd1 cmd2 ... cmdn file2\n"  

/*        struct        */

typedef struct s_data
{
	char	**envp;
	char	**av;
	int		ac;
	int		fd_in;
	int		fd_out;
	int		*pipe;
	char	*cmd_path;
	int		fd[2];
	int		heredoc_fd[2];
	char	**cmd_options;
	int		is_first;
	int		is_last;
	int		is_heredoc;
	int		is_bonus;
	char	*delimiter;
}	t_data;

char	*get_cmd(char *cmd, t_data *data);
void	free_strs(char *str, char **tab);
void	init_main(t_data *sata, int ac, char **av, char **envp);
void	exit_error(char *msg, t_data *data);

#endif
