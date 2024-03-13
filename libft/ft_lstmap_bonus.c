/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:54:10 by aserebry          #+#    #+#             */
/*   Updated: 2023/10/30 14:54:10 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;

	if (!lst)
		return (NULL);
	else
	{
		list = ft_lstnew(f(lst->content));
		if (!list)
		{
			ft_lstclear(&list, del);
			return (NULL);
		}
		list->next = ft_lstmap(lst->next, f, del);
		return (list);
	}
}
