/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:00:52 by aserebry          #+#    #+#             */
/*   Updated: 2024/03/05 13:05:34 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_heredoc(char *str, int fd1, int fd2)
{
	str = get_next_line(fd1);
	while (str)
	{
		write(fd2, str, ft_strlen(str));
		free(str);
		str = get_next_line(fd1);
	}
}

static void	handle_heredoc(char *str[2], char *delim, int fd)
{
	int	fdtmp[2];

	fdtmp[0] = open(".tmpfile", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	str[1] = readline("> ");
	while (g_status != 130 && str[1] != NULL
		&& (ft_strncmp(delim, str[1], ft_strlen(str[1])) != 0 || \
		str[1][0] == '\0'))
	{
		write(fdtmp[0], str[1], ft_strlen(str[1]));
		write(fdtmp[0], "\n", 1);
		free(str[1]);
		str[1] = readline("> ");
	}
	close(fdtmp[0]);
	fdtmp[1] = open(".tmpfile", O_RDONLY);
	print_heredoc(str[0], fdtmp[1], fd);
	close(fdtmp[1]);
	free(str[0]);
	free(str[1]);
	unlink(".tmpfile");
}

int	get_here_doc(char *str[2], char *aux[2])
{
	int	fd[2];

	g_status = 0;
	if (pipe(fd) == -1)
	{
		mini_perror(PIPERR, NULL, 1);
		return (-1);
	}
	handle_heredoc(str, aux[0], fd[WRITE_END]);
	close(fd[WRITE_END]);
	if (g_status == 130)
	{
		close(fd[READ_END]);
		return (-1);
	}
	return (fd[READ_END]);
}
