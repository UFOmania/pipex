/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 00:35:33 by massrayb          #+#    #+#             */
/*   Updated: 2024/11/12 00:37:21 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*head;

	if (lst == NULL || del == NULL || *lst == NULL )
		return ;
	head = *lst;
	while (head)
	{
		tmp = head;
		head = head->next;
		ft_lstdelone(tmp, del);
	}
	*lst = NULL;
}
