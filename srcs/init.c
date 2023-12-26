#include "pipex.h"

static void  clean_struct(t_data *data)
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

void  init_struct(t_data *data, int ac, char **av, char**envp)
{
	clean_struct(data);
	data->ac = ac;
	data->av = av;
	data->envp = envp;
	data->is_first = 1;
	data->fd_in = open(av[1], O_RDONLY);
	if (data->fd_in == -1)
		exit(EXIT_FAILURE);
	data->fd_out = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->fd_out == -1)
		exit(EXIT_FAILURE);
}
