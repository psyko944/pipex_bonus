/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekherbo <mekherbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:19:23 by mekherbo          #+#    #+#             */
/*   Updated: 2023/11/02 13:19:43 by mekherbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	if (n < 0)
		count++;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*ft_malloc(int len)
{
	char	*res;

	res = NULL;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	res[len] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	long	nbr;
	int		len;

	nbr = n;
	len = ft_len(n);
	res = ft_malloc(len);
	if (n < 0)
		nbr = -nbr;
	if (n == 0)
	{
		res[0] = '0';
	}
	while (len-- > 0)
	{
		res[len] = nbr % 10 + 48;
		nbr = nbr / 10;
	}
	if (n < 0)
		res[0] = '-';
	return (res);
}
