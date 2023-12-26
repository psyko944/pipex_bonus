/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekherbo <mekherbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:24:53 by mekherbo          #+#    #+#             */
/*   Updated: 2023/11/11 08:11:40 by mekherbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	check_set(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		end;
	int		i;
	int		start;

	i = 0;
	end = ft_strlen(s1);
	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (check_set(set, s1[start]))
		start++;
	while (end > start && check_set(set, s1[end - 1]))
		end--;
	trim = malloc(sizeof(char) * (end - start + 1));
	if (trim == NULL)
		return (NULL);
	while (start < end)
	{
		trim[i++] = s1[start++];
	}
	trim[i] = '\0';
	return (trim);
}
