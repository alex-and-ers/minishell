/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:00:22 by aserebry          #+#    #+#             */
/*   Updated: 2024/03/05 13:05:11 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	cd_error2(char **str[2], t_cmd *p)
{
	char	*aux;

	aux = ft_getenv("OLDPWD", p->envp, 6);
	if (aux)
	{
		g_status = chdir(aux) == -1;
		if (!g_status)
		{
			p->envp = ft_setenv("OLDPWD", str[1][1], p->envp, 6);
			ft_putstr_m_fd(aux, 1);
			ft_putstr_m_fd("\n", 1);
			free(aux);
		}
		else
			mini_perror(-1, "cd: OLDPWD not set", 1);
	}
	else
	{
		g_status = 1;
		ft_putstr_m_fd("minishell: OLDPWD not set\n", 2);
	}
	return ;
}

void	cd_error(char **str[2], t_cmd *p)
{
	DIR		*dir;

	dir = NULL;
	if (str[0][1])
		dir = opendir(str[0][1]);
	if (str[0][1] && !ft_strcmp(str[0][1], "-"))
		return (cd_error2(str, p));
	if (!str[0][1] && str[1][0] && !str[1][0][0])
	{
		g_status = 1;
		ft_putstr_m_fd("minishell: HOME not set\n", 2);
	}
	if (str[1][0] && !str[0][1])
		g_status = chdir(str[1][0]) == -1;
	if (str[0][1] && dir && access(str[0][1], F_OK) != -1)
		chdir(str[0][1]);
	else if (str[0][1] && access(str[0][1], F_OK) == -1)
		mini_perror(NDIR, str[0][1], 1);
	else if (str[0][1])
		mini_perror(NOT_DIR, str[0][1], 1);
	if (str[0][1] && dir)
		closedir(dir);
}

int	ft_cd(t_cmd *p)
{
	char	**str[2];
	char	*aux;

	g_status = 0;
	str[0] = ((t_mini *)p->cmds->content)->full_cmd;
	aux = ft_getenv("HOME", p->envp, 4);
	if (!aux)
		aux = ft_strdup("");
	str[1] = ft_extend_matrix(NULL, aux);
	free(aux);
	aux = getcwd(NULL, 0);
	str[1] = ft_extend_matrix(str[1], aux);
	free(aux);
	cd_error(str, p);
	if (!g_status)
		p->envp = ft_setenv("OLDPWD", str[1][1], p->envp, 6);
	aux = getcwd(NULL, 0);
	if (!aux)
		aux = ft_strdup("");
	str[1] = ft_extend_matrix(str[1], aux);
	free(aux);
	p->envp = ft_setenv("PWD", str[1][2], p->envp, 3);
	ft_free_matrix(&str[1]);
	return (g_status);
}
