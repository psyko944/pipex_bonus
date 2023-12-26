/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekherbo <mekherbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:24:44 by mekherbo          #+#    #+#             */
/*   Updated: 2023/11/02 13:24:47 by mekherbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*retval;
	int		i;

	if (str == NULL)
	{
		return (NULL);
	}
	i = ft_strlen(str);
	retval = (char *)str;
	while (i >= 0)
	{
		if (retval[i] == (char)c)
			return (retval + i);
		i--;
	}
	return (0);
}
