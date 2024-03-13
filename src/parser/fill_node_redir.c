/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_node_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 16:54:06 by aserebry          #+#    #+#             */
/*   Updated: 2024/02/28 10:47:37 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_redir_symbols(char *tmp)
{
	if (tmp[0] == '<' && tmp[1] == '<' && tmp[2] == '<')
		return (-1);
	else if (tmp[0] == '>' && tmp[1] == '>' && tmp[2] == '>')
		return (-2);
	else if (tmp[0] == '<' && tmp[1] == '<' && tmp[2] == '>')
		return (-2);
	else if (tmp[0] == '>' && tmp[1] == '>' && tmp[2] == '<')
		return (-1);
	else if ((tmp[0] == '>' && tmp[1] == '<')
		|| (tmp[1] == '>' && tmp[2] == '<'))
		return (-3);
	return (0);
}

static int	handle_multiple_redir(char **args)
{
	int		i;
	int		j;
	int		res;
	char	tmp[3];

	i = -1;
	while (args && args[++i])
	{
		if ((ft_strcmp(args[i], "<") && ft_strcmp(args[i], ">")) == 0)
		{
			j = 0;
			tmp[0] = 0;
			tmp[1] = 0;
			tmp[2] = 0;
			while ((i + 3 < ft_matrixlen(args)) && j != 3)
			{
				tmp[j] = args[i + j][0];
				j++;
			}
			res = check_redir_symbols(tmp);
			if (res != 0)
				return (res);
		}
	}
	return (0);
}

int	check_redir(char **args)
{
	int	is_err;
	int	i;

	is_err = 0;
	i = 0;
	while (args && args[i])
	{
		if (!ft_strcmp(args[i], ">") && args[i + 1]
			&& !ft_strcmp(args[i], "<"))
		{
			mini_perror(-1, "mini: syntax error unexpected token `<'", 258);
			return (-1);
		}
		i++;
	}
	is_err = handle_multiple_redir(args);
	if (is_err == -1 || is_err == -2 || is_err == -3)
	{
		if (is_err == -1 || is_err == -3)
			mini_perror(-1, "mini: syntax error unexpected token `<'", 258);
		else if (is_err == -2)
			mini_perror(-1, "mini: syntax error unexpected token `>'", 258);
		ft_free_matrix(&args);
	}
	return (is_err);
}

void	norminette_makes_me_do_this(int *i, char **args, t_list *cmds[2])
{
	(*i) += args[*i][0] == '|';
	ft_lstadd_back(&cmds[0], ft_lstnew(mini_init()));
	cmds[1] = ft_lstlast(cmds[0]);
}
