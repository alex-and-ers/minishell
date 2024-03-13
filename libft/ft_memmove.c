/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:54:54 by aserebry          #+#    #+#             */
/*   Updated: 2023/10/30 14:54:54 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;

	if (!dst && !src)
		return (dst);
	dest = (unsigned char *) dst;
	source = (unsigned char *) src;
	if (dst < src)
	{
		while (len--)
			*dest++ = *source++;
	}
	else
	{
		while (len--)
			dest[len] = source[len];
	}
	return (dst);
}
