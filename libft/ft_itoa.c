/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:52:54 by aserebry          #+#    #+#             */
/*   Updated: 2023/10/30 14:52:54 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(int n, unsigned int *num, int *sign)
{
	int	size;

	if (n >= 0)
	{
		*num = n;
		*sign = 1;
	}
	else
	{
		*num = -n;
		*sign = 0;
	}
	if (n > 0)
		size = 0;
	else
		size = 1;
	while (n)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	unsigned int	num;
	int				sign;
	int				size;
	char			*result;

	size = get_size(n, &num, &sign);
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result[size--] = '\0';
	while (num >= 10)
	{
		result[size] = num % 10 + '0';
		num = num / 10;
		size--;
	}
	result[size] = num % 10 + '0';
	if (!sign)
		result[0] = '-';
	return (result);
}
