/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_empty_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:59:57 by aserebry          #+#    #+#             */
/*   Updated: 2024/02/02 15:59:57 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	**bubble(char **args, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strncmp(args[j], args[j + 1], ft_strlen(args[j]) + 1) > 0)
			{
				temp = args[j];
				args[j] = args[j + 1];
				args[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	return (args);
}

static char	**prepare_env_arr(char **envp)
{
	int		i;
	int		size;
	char	**keys;

	if (envp == NULL)
		return (NULL);
	size = ft_matrixlen(envp);
	keys = (char **) malloc(sizeof(char *) * (size + 1));
	if (!keys)
		mini_perror(MEM, "Malloc", 2);
	i = -1;
	while (envp[++i])
		keys[i] = ft_strdup(envp[i]);
	keys[i] = NULL;
	return (bubble(keys, size));
}

static void	free_export_arr(char **keys, int size)
{
	int	i;

	if (!keys)
		return ;
	i = -1;
	while (++i < size)
		free(keys[i]);
	free(keys);
}

void	process_empty_args(char **envp)
{
	int		i;
	int		j;
	char	**keys;

	i = -1;
	keys = prepare_env_arr(envp);
	while (keys && keys[++i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		j = -1;
		while (keys[i][++j])
		{
			write(STDOUT_FILENO, &keys[i][j], 1);
			if (keys[i][j] == '=')
				ft_putstr_fd("\"", STDOUT_FILENO);
			if (keys[i][j + 1] == '\0')
				ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	if (keys)
		free_export_arr(keys, i);
}
