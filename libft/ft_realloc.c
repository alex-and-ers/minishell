/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:19:18 by aserebry          #+#    #+#             */
/*   Updated: 2023/12/30 16:19:21 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *initial_ptr, size_t initial_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = ft_calloc(1, new_size);
	if (new_ptr)
	{
		if (initial_size < new_size)
			ft_memmove(new_ptr, initial_ptr, initial_size);
		else
		{
			ft_memmove(new_ptr, initial_ptr, new_size);
			((char *)new_ptr)[new_size - 1] = 0;
		}
	}
	free(initial_ptr);
	initial_ptr = NULL;
	return (new_ptr);
}
