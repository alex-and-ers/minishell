/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:00:30 by aserebry          #+#    #+#             */
/*   Updated: 2024/03/05 13:05:24 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	builtin(t_cmd *prompt, t_list *cmd, int *is_exit, int n)
{
	char	**a;

	while (cmd)
	{
		a = ((t_mini *)cmd->content)->full_cmd;
		n = 0;
		if (a)
			n = ft_strlen(*a);
		if (a && !ft_strncmp(*a, "exit", n) && n == 4)
			g_status = mini_exit(cmd, is_exit);
		else if (!cmd->next && a && !ft_strncmp(*a, "cd", n) && n == 2)
			g_status = ft_cd(prompt);
		else if (!cmd->next && a && !ft_strncmp(*a, "export", n) && n == 6)
			g_status = ft_export(prompt);
		else if (!cmd->next && a && !ft_strncmp(*a, "unset", n) && n == 5)
			g_status = ft_unset(prompt);
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			exec_cmd(prompt, cmd);
		}
		cmd = cmd->next;
	}
	return (g_status);
}

int	is_builtin(t_mini *n)
{
	int		i;

	if (!n->full_cmd)
		return (0);
	if ((n->full_cmd && ft_strchr(*n->full_cmd, '/')) || (n->full_path && \
		ft_strchr(n->full_path, '/')))
		return (0);
	i = ft_strlen(*n->full_cmd);
	if (!ft_strncmp(*n->full_cmd, "pwd", i) && i == 3)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "env", i) && i == 3)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "cd", i) && i == 2)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "export", i) && i == 6)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "unset", i) && i == 5)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "echo", i) && i == 4)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "history", i) && i == 4)
		return (1);
	if (!ft_strncmp(*n->full_cmd, "exit", i) && i == 4)
		return (1);
	return (0);
}
