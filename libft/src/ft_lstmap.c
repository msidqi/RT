/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 19:00:00 by msidqi            #+#    #+#             */
/*   Updated: 2018/10/19 03:25:39 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*begin;
	t_list		*l;

	if (!lst)
		return (NULL);
	l = NULL;
	if (!(l = f(lst)))
		return (NULL);
	begin = l;
	lst = lst->next;
	while (lst != NULL)
	{
		if (!(l->next = f(lst)))
			return (NULL);
		lst = lst->next;
		l = l->next;
	}
	return (begin);
}
