/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:58:34 by aserebry          #+#    #+#             */
/*   Updated: 2023/10/30 14:58:34 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_size;

	i = 0;
	dst_size = 0;
	while (dst_size < dstsize && dst[dst_size])
		dst_size++;
	while ((src[i] != '\0') && ((dst_size + i + 1) < dstsize))
	{
		dst[dst_size + i] = src[i];
		i++;
	}
	if (dst_size != dstsize)
		dst[dst_size + i] = '\0';
	return (dst_size + ft_strlen(src));
}
