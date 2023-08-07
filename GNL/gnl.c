/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:19:19 by msamhaou          #+#    #+#             */
/*   Updated: 2023/08/07 12:00:59 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

static char	*ft_read(char *readed, int fd, t_collector **col)
{
	char	*buff;
	int		rdb;
	static int i;
	buff = c_malloc(sizeof(char) * (BUFFER_SIZE + 1), col);
	if (!buff)
	{
		ft_free_addr(*col);
		ft_free_collector(col);
		return (NULL);
	}
	rdb = 1;
	while (rdb > 0 && !ft_isnewline(readed))
	{
		rdb = read(fd, buff, BUFFER_SIZE);
		buff[rdb] = '\0';
		readed = ft_gstrjoin(readed, buff, col);
		if (!readed)
		{
			ft_free_addr(*col);
			ft_free_collector(col);
			exit(1);

		}
		if (!readed[0] && rdb == 0)
			return (NULL);

	}
	return (readed);
}

char	*ft_line(char *str, t_collector **col)
{
	int		i;
	char	*line;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n')
		i++;
	line = c_malloc(sizeof(char) * (i + 1), col);
	if (!line)
	{
		ft_free_addr(*col);
		ft_free_collector(col);
		return (NULL);
	}
	ft_strlcpy(line, str, i + 1);
	return (line);
}

static char	*ft_next(char *str, t_collector **col)
{
	char	*next;
	size_t	len;
	size_t	j;

	if (!str)
		return (NULL);
	len = ft_linelen(str);
	next = (char *)c_malloc((ft_strlen(str) - len + 1) * sizeof(char), col);
	if (!next)
	{
		ft_free_addr(*col);
		ft_free_collector(col);
		return (NULL);
	}
	len++;
	j = 0;
	while (str[len])
	{
		next[j] = str[len];
		len++;
		j++;
	}
	next[j] = '\0';
	return (next);
}

char	*gnl(int fd, t_collector **col)
{
	static char	*readed;
	char		*line;

	readed = ft_read(readed, fd, col);
	line = ft_line(readed, col);
	readed = ft_next(readed, col);
	return (line);
}
