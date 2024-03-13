/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:59:45 by aserebry          #+#    #+#             */
/*   Updated: 2024/02/02 15:59:45 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	key_validator(const char *s)
{
	int	i;

	i = 1;
	if (s == NULL || *s == '\0')
		return (0);
	if (!(s[0] == '_' || (s[0] >= 'a' && s[0] <= 'z')
			|| (s[0] >= 'A' && s[0] <= 'Z')))
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (!(s[i] == '_' || ft_isalnum(s[i])))
			return (0);
		i++;
	}
	return ((s[i] == '=' && i > 0) || (s[i] == '\0' && i > 0));
}

int	export_err_not_valid_key(int errcode)
{
	return (errcode);
}
