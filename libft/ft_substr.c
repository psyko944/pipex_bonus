/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekherbo <mekherbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:24:59 by mekherbo          #+#    #+#             */
/*   Updated: 2023/11/02 13:25:01 by mekherbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_diff(size_t size1, size_t size2)
{
	if (size1 < size2)
		return (size1);
	else
		return (size2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	s = s + start;
	len = ft_diff(len, ft_strlen(s));
	newstr = ft_calloc(1, len + 1);
	if (!newstr)
		return (0);
	return ((char *)ft_memcpy(newstr, s, len));
}
