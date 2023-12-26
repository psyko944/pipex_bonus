#include "pipex.h"

void  free_strs(char *str, char **tab)
{
	if (str && *str)
		free(str);
	if (tab && *tab)
	{
		int	i;

		i = -1;
		while (tab[++i])
			free(tab[i]);
		free(tab);
	}
}

/*int	ft_error(char *msg, char *msg2, char *error)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(msg2, 2);
	ft_putstr_fd(msg3, 2);
}*/
