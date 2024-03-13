/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:40:40 by aserebry          #+#    #+#             */
/*   Updated: 2023/11/30 12:40:40 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	free_buff(int read_res, char *buff)
{
	if (buff)
		free(buff);
	return (read_res);
}

int	ft_strlen_gnl(const char *s)
{
	int	size;

	size = 0;
	if (!s)
		return (0);
	while (s[size] != '\0')
		size++;
	return (size);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len1;
	int		len2;
	char	*result;

	len1 = ft_strlen_gnl(s1);
	len2 = ft_strlen_gnl(s2);
	result = malloc(sizeof(char *) * (len1 + len2 + 1));
	if (!result)
	{
		free(s1);
		return (NULL);
	}
	i = -1;
	j = -1;
	while (++i < len1)
		result[i] = s1[i];
	while (++j < len2)
		result[i + j] = s2[j];
	result[j + i] = '\0';
	if (s1)
		free(s1);
	return (result);
}

int	ft_malloc(char **ptr, unsigned int size)
{
	*ptr = malloc(sizeof(char *) * (size + 1));
	if (!(*ptr))
		return (-1);
	return (0);
}
