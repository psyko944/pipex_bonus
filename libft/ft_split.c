/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekherbo <mekherbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:22:57 by mekherbo          #+#    #+#             */
/*   Updated: 2023/11/02 13:22:59 by mekherbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_c(char car, char c)
{
	if (car == c)
		return (1);
	return (0);
}

static int	count_word(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] && is_in_c(str[i], c))
			i++;
		if (str[i] && !is_in_c(str[i], c))
		{
			count++;
			while (str[i] && !is_in_c(str[i], c))
				i++;
		}
	}
	return (count);
}

static char	*ft_word(char *str, char c)
{
	int		i;
	char	*word;

	word = NULL;
	i = 0;
	while (str[i] && !is_in_c(str[i], c))
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	if (word == NULL)
		return (0);
	i = 0;
	while (str[i] && !is_in_c(str[i], c))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**ft_free(char **tab, int i)
{
	while (i)
	{
		free(tab[i]);
		tab[i] = NULL;
		i--;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	char	*str;

	tab = NULL;
	str = (char *)s;
	tab = (char **)malloc(sizeof(char *) * (count_word(str, c) + 1));
	if (tab == NULL)
		return (0);
	i = 0;
	while (*str)
	{
		if (*str && is_in_c(*str, c))
			str++;
		if (*str && !is_in_c(*str, c))
		{
			tab[i] = ft_word(str, c);
			if (tab[i++] == NULL)
				return (ft_free((char **)tab, i++));
			while (*str && !is_in_c(*str, c))
				str++;
		}
	}
	tab[i] = NULL;
	return (tab);
}
