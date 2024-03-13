/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:00:02 by aserebry          #+#    #+#             */
/*   Updated: 2024/03/02 13:58:34 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	var_in_envp(char *argv, char **envp, int ij[2])
{
	int	pos;

	ij[1] = 0;
	pos = ft_strchr_i(argv, '=');
	if (pos == -1)
		pos = ft_strlen(argv) - 1;
	while (envp[ij[1]])
	{
		if (!ft_strncmp(envp[ij[1]], argv, pos + 1))
			return (1);
		ij[1]++;
	}
	return (0);
}

static char	*create_err_msg(char *key)
{
	char	*msg;

	msg = ft_strjoin("minishell: export: `", key);
	msg = ft_strjoin(msg, "': not a valid identifier\n");
	return (msg);
}

static int	process_multi_args(t_cmd *prompt, char **argv, int *ij)
{
	char	*msg;

	ij[0] = 1;
	ij[3] = 0;
	while (argv[ij[0]])
	{
		ij[2] = var_in_envp(argv[ij[0]], prompt->envp, ij);
		if (ij[2] == 1)
		{
			free(prompt->envp[ij[1]]);
			prompt->envp[ij[1]] = ft_strdup(argv[ij[0]]);
		}
		else if (!key_validator(argv[ij[0]]))
		{
			msg = create_err_msg(argv[ij[0]]);
			ft_putstr_fd(msg, STDERR_FILENO);
			ij[3] = 1;
			free(msg);
		}
		else if (!ij[2])
			prompt->envp = ft_extend_matrix(prompt->envp, argv[ij[0]]);
		ij[0]++;
	}
	return (ij[3]);
}

int	ft_export(t_cmd *prompt)
{
	int		ij[4];
	char	**argv;

	argv = ((t_mini *)prompt->cmds->content)->full_cmd;
	if (ft_matrixlen(argv) >= 2)
	{
		ij[3] = process_multi_args(prompt, argv, ij);
		if (ij[3])
			return (export_err_not_valid_key(1));
	}
	else
		process_empty_args(prompt->envp);
	return (0);
}
