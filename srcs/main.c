#include "pipex.h"

/*static void	child_one(t_data *data)
{
	dup2(data->fd_in, STDIN_FILENO);
	if (data->fd_in != -1)
		close(data->fd_in);
	dup2(data->pipe[1], 1);
	close(data->pipe[1]);
	close(data->pipe[0]);
	data->cmd_options = ft_split(data->av[2], ' ');
	data->cmd_path = get_cmd(data->cmd_options[0], data);
	if (execve(data->cmd_path, data->cmd_options, data->envp) == -1)
		exit(EXIT_FAILURE);
}

static void	child_two(t_data *data)
{
	dup2(data->pipe[0], STDIN_FILENO);
	close(data->pipe[0]);
	close(data->pipe[1]);
	dup2(data->fd_out, STDOUT_FILENO);
	if (data->fd_out != -1)
		close(data->fd_out);
	data->cmd_options = ft_split(data->av[3], ' ');
	data->cmd_path = get_cmd(data->cmd_options[0], data);
	if (execve(data->cmd_path, data->cmd_options, data->envp) == -1)
		exit(EXIT_FAILURE);
}*/

static void	child_runtime(t_data *data)
{
	ft_putstr_fd("on est dans le fils\n", 2);
	data->cmd_options = ft_split(*data->av, ' ');
	//printf("cmd = %s\n", data->cmd_options[0]);
	data->cmd_path = get_cmd(data->cmd_options[0], data);
	if (execve(data->cmd_path, data->cmd_options, data->envp) == -1)
	{
		write(2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
}

static void	runtime(t_data *data, int i)
{
	//int	  fd[2];
	pid_t pid;

	if (i + 2 == data->ac)
		data->is_last = 1;
	if (pipe(data->fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0 && !data->is_last)
	{
		write(2, "test\n", 5); 
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[0]);
		close(data->fd[1]);
		child_runtime(data);
	}
	else if (pid == 0)
	{
		write(2, "allo\n", 5);
		if (data->is_last)
			dup2(data->fd_out, STDOUT_FILENO);
		if (data->fd_out != -1)
			close(data->fd_out);
		close(data->fd[0]);
		close(data->fd[1]);
		child_runtime(data);
	}
	else 
	{
		wait(NULL);
		dup2(data->fd[0], STDIN_FILENO);
		data->is_first = 0;
		close(data->fd[1]);
		close(data->fd[0]);
	}
}
int main(int ac, char **av, char **envp)
{
	t_data	data;
	int		i;
	if (ac >= 5)
	{
		init_struct(&data, ac, av, envp);
		i = 2;
		dup2(data.fd_in, STDIN_FILENO);
		if (data.fd_in != -1)
			close(data.fd_in);
		data.av++;
		data.av++;
		data.is_first = 1;
		while (i < ac - 1)
		{
			//printf("av = %s\n", *data.av);
			runtime(&data, i);
			/*if (pipe(data.pipe) ==perror("pipe");
				return (1);
				perror("pipe");
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				return (2);
			}
			else if (pid == 0)
			{
				child_one(&data);
			}
			else
			{
				wait(NULL);
				pid2 = fork();
				if (pid2 == -1)
					exit(EXIT_FAILURE);
				else if (pid2 == 0)
					child_two(&data);
				else 
				{	
					close(data.pipe[1]);
					close(data.pipe[0]);
				}*/
				//printf("i = %d\n", i);
				i++;
				data.av++;
		}
		/*char buffer[100];
		read(data.fd[0], &buffer, sizeof(buffer));
		ft_putstr_fd(buffer, 2);*/
	}
	else {
		printf("too few arguments\n./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n");
		return (1);
	}
	return (0);
}
