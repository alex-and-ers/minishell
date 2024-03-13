/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aserebry <aserebry@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:40:48 by aserebry          #+#    #+#             */
/*   Updated: 2023/11/30 12:40:48 by aserebry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	int	nl_pos(char *buff)
{
	int	i;
	int	len;

	if (!buff)
		return (-1);
	len = ft_strlen_gnl(buff);
	i = -1;
	while (++i < len)
	{
		if (buff[i] == '\n')
			return (i);
	}
	return (-1);
}

static	void	move_line_ptr(char *buff)
{
	int	i;
	int	len;
	int	pos;

	if (!buff)
		return ;
	pos = nl_pos(buff);
	if (pos == -1)
		return ;
	len = ft_strlen_gnl(buff);
	i = 0;
	while (pos + i + 1 < len)
	{
		buff[i] = buff[pos + i + 1];
		i++;
	}
	buff[i] = '\0';
}

static int	read_to_buff(int fd, char **buffs)
{
	char	*buff;
	int		read_res;

	read_res = ft_malloc(&buff, BUFFER_SIZE);
	if (read_res == -1)
		return (0);
	buff[0] = '\0';
	if (nl_pos(buffs[fd]) == -1)
	{
		while (nl_pos(buff) == -1)
		{
			read_res = read(fd, buff, BUFFER_SIZE);
			if (read_res <= 0)
			{
				if (read_res == -1)
					return (free_buff(-2, buff));
				return (free_buff(read_res, buff));
			}
			buff[read_res] = '\0';
			buffs[fd] = ft_strjoin_gnl(buffs[fd], buff);
			if (!buffs[fd] || !buff)
				return (free_buff(read_res, buff));
		}
	}
	return (free_buff(read_res, buff));
}

static char	*get_line_from_buffs(char *buff)
{
	int		i;
	int		pos;
	int		len;
	char	*result;

	if (!ft_strlen_gnl(buff) || !buff)
		return (NULL);
	pos = nl_pos(buff);
	if (pos != -1)
		len = pos + 1;
	else
		len = (ft_strlen_gnl(buff));
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len)
		result[i] = buff[i];
	result[i] = '\0';
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffs[OPEN_MAX];
	char		*result;
	int			read_res;
	int			i;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	read_res = read_to_buff(fd, buffs);
	result = get_line_from_buffs(buffs[fd]);
	if ((buffs[fd] && !result) || (nl_pos(buffs[fd]) == -1 && read_res <= 0))
	{
		if (read_res == -2 && result)
		{
			i = 0;
			while (buffs[fd][i])
				buffs[fd][i++] = '\0';
			free(result);
			return (NULL);
		}
		free(buffs[fd]);
		buffs[fd] = NULL;
	}
	move_line_ptr(buffs[fd]);
	return (result);
}
