/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_link_two_lists.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 15:58:49 by msidqi            #+#    #+#             */
/*   Updated: 2019/07/17 15:59:07 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_link_two_lists(t_list *head_1, t_list *head_2)
{
	if (head_1 == NULL || head_2 == NULL)
		return ;
	while (head_1 != NULL)
	{
		head_1 = head_1->next;
	}
	head_1->next = head_2;
}
