
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

/*        struct        */

typedef struct s_data
{
	char	**envp;
	char	**av;
	int		ac;
	int		fd_in;
	int		fd_out;
	int		*pipe;
	char  	*cmd_path;
	int		fd[2];
	char  	**cmd_options;
	int		is_first;
	int		is_last;
}	t_data;

char  *get_cmd(char *cmd, t_data *data);
void  free_strs(char *str, char **tab);
void  init_struct(t_data *sata, int ac, char **av, char **envp);

#endif
