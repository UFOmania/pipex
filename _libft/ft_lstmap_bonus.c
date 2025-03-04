/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: massrayb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 04:29:41 by massrayb          #+#    #+#             */
/*   Updated: 2024/11/12 20:14:19 by massrayb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	void	*f_cnt;
	t_list	*ptr;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	head = NULL;
	while (lst)
	{
		f_cnt = f(lst->content);
		ptr = ft_lstnew(f_cnt);
		if (!ptr)
		{
			if (f_cnt)
				del(f_cnt);
			ft_lstclear(&head, del);
			return (NULL);
		}
		ft_lstadd_back(&head, ptr);
		lst = lst->next;
	}
	return (head);
}
