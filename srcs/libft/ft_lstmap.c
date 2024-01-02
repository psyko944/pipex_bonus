/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mekherbo <mekherbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:20:59 by mekherbo          #+#    #+#             */
/*   Updated: 2023/11/05 11:32:36 by mekherbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

/*t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;

	if (!lst || !f || del)
		return (NULL);
	new = NULL;
	temp = new;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			ft_lstclear(&temp, del);
			return (NULL);
		}
		ft_lstadd_back(&temp, new);
		lst = lst->next;
	}
	return (temp);
}*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*node;
	t_list	*cpy;

	if (!lst || !f || !del)
		return (NULL);
	cpy = lst;
	newlst = NULL;
	while (cpy)
	{
		node = ft_lstnew(f(cpy->content));
		if (!node)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, node);
		cpy = cpy->next;
	}
	return (newlst);
}
