/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:01:17 by aserebry          #+#    #+#             */
/*   Updated: 2024/03/05 13:03:52 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand_path(char *str, int i, int quotes[2], char *var)
{
	char	*path;
	char	*aux;

	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (!quotes[0] && !quotes[1] && str[i] == '~' && (i == 0 || \
			str[i - 1] != '$'))
		{
			aux = ft_substr(str, 0, i);
			path = ft_strjoin(aux, var);
			free(aux);
			aux = ft_substr(str, i + 1, ft_strlen(str));
			free(str);
			str = ft_strjoin(path, aux);
			free(aux);
			free(path);
			return (expand_path(str, i + ft_strlen(var) - 1, quotes, var));
		}
	}
	free(var);
	return (str);
}

static void	handle_dollar_and_question(char *str, int i, char **var, int pid)
{
	if (str[i] == '$')
		*var = ft_itoa(pid);
	else if (str[i] == '?')
		*var = ft_itoa(g_status);
	else
		*var = strdup("");
}

static char	*get_substr_var(char *str, int i, t_cmd *prompt)
{
	char	*aux;
	char	*var;
	char	*path;
	int		var_len;

	var_len = 0;
	while (str[i + var_len] && (ft_isalnum(str[i + var_len])
			|| str[i + var_len] == '_'))
		var_len++;
	var = ft_getenv(&str[i], prompt->envp, var_len);
	if (!var)
		handle_dollar_and_question(str, i, &var, prompt->pid);
	aux = ft_substr(str, 0, i - 1);
	path = ft_strjoin(aux, var);
	free(aux);
	if (str[i] == '$' || str[i] == '?')
		i++;
	aux = ft_strjoin(path, &str[i + var_len]);
	free(var);
	free(path);
	free(str);
	return (aux);
}

char	*expand_vars(char *str, int i, int quotes[2], t_cmd *prompt)
{
	quotes[0] = 0;
	quotes[1] = 0;
	while (str && str[++i])
	{
		quotes[0] = (quotes[0] + (!quotes[1] && str[i] == '\'')) % 2;
		quotes[1] = (quotes[1] + (!quotes[0] && str[i] == '\"')) % 2;
		if (!quotes[0] && str[i] == '$' && str[i + 1] && \
			((ft_strchars_i(&str[i + 1], "/~%^{}:; ") && !quotes[1]) || \
			(ft_strchars_i(&str[i + 1], "/~%^{}:;\" ") && quotes[1])))
			return (expand_vars(get_substr_var(str, ++i, prompt), -1, \
				quotes, prompt));
	}
	return (str);
}
