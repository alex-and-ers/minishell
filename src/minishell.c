/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:57:08 by aserebry          #+#    #+#             */
/*   Updated: 2024/03/06 11:13:48 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_cmd	check_home_env(t_cmd input)
{
	char	*str;

	str = ft_getenv("HOME", input.envp, 4);
	if (!str)
	{
		str = getcwd(NULL, 0);
		input.envp = ft_setenv("HOME", str, input.envp, 4);
	}
	free (str);
	return (input);
}

static void	mini_getpid(t_cmd *p)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		mini_perror(FORKERR, NULL, 1);
		ft_free_matrix(&p->envp);
		exit(1);
	}
	if (!pid)
	{
		ft_free_matrix(&p->envp);
		exit(1);
	}
	waitpid(pid, NULL, 0);
	p->pid = pid - 1;
}

static t_cmd	init_vars(t_cmd input, char *str, char **argv)
{
	char	*num;

	str = getcwd(NULL, 0);
	input.envp = ft_setenv("PWD", str, input.envp, 3);
	free(str);
	str = ft_getenv("SHLVL", input.envp, 5);
	if (!str || ft_atoi(str) <= 0)
		num = ft_strdup("1");
	else
		num = ft_itoa(ft_atoi(str) + 1);
	free(str);
	input.envp = ft_setenv("SHLVL", num, input.envp, 5);
	free(num);
	str = ft_getenv("PATH", input.envp, 4);
	if (!str)
		input.envp = ft_setenv("PATH", \
		"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin", input.envp, 4);
	free(str);
	str = ft_getenv("_", input.envp, 1);
	if (!str)
		input.envp = ft_setenv("_", argv[0], input.envp, 1);
	free(str);
	input = check_home_env(input);
	return (input);
}

static t_cmd	init_prompt(char **argv, char **envp)
{
	t_cmd	input;
	char	*str;

	str = NULL;
	input.cmds = NULL;
	input.envp = ft_dup_matrix(envp);
	g_status = 0;
	mini_getpid(&input);
	input = init_vars(input, str, argv);
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	*out;
	t_cmd	input;

	input = init_prompt(argv, envp);
	while (argv && argc)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		str = mini_getprompt();
		if (str)
			out = readline(str);
		else
			out = readline("guest@minishell $ ");
		free(str);
		if (!check_args(out, &input))
			break ;
	}
	exit(g_status);
}
