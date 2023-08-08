/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_chek.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:38:32 by msamhaou          #+#    #+#             */
/*   Updated: 2023/08/08 18:51:49 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

bool	ft_one_of_chr(char c)
{
	return(c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '0');
}

int	ft_check_zero_surround(char	*row, int back, int	next)
{
	int	i;

	i = 1;
	while (row[i])
	{
		if (row[i] == '0')
			if (i > back || i > next)
				return (-1);
		i++;
	}
}

int	ft_check_valid_map_characthers(const char *str, int *pos)
{
	char	*s;

	s = (char *)str;
	while (*s)
	{
		if (*s != '0' && *s != '1' && *s != 'N' && *s != 'S' && *s != 'W' && *s != 'E' && *s != ' ')
			return (-1);
		if (*s == 'N' || *s == 'S' || *s == 'W' || *s == 'E')
			(*pos)++;
		if (*pos > 1)
			return (-1);
		s++;
	}
	return (0);
}

int	ft_map_strchr(const char *str)
{
	char	*s;

	s = (char *)str;
	while (*s)
	{
		if (*s == 'N' || *s == 'S' || *s == 'W' || *s == 'E' || *s == '0')
			return (1);
		s++;
	}
	return (0);
}

char	*ft_find_map(int fd, t_collector **col)
{
	char	*line;

	line = gnl(fd, col);
	while (line && line[0] == '\0')
		line = gnl(fd, col);
	if (!line)
		ft_free_error_type(col, 4);
	if (!ft_strchr(line,'1'))
	{
		ft_free_error_type(col, 4);
	}

	return (line);
}

t_map_row	*ft_get_map_compo(char *line, int fd, t_collector **col)
{
	t_map_row	*row;

	row = NULL;
	while(line)
	{
		ft_row_add_back(&row, ft_new_row(line, col));
		line = gnl(fd, col);
	}
	return (row);
}

int	ft_check_map_compo(t_map_row *row)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (row)
	{
		if (ft_check_valid_map_characthers(row->row, &count) == -1)
			return (-1);
		if (row->row[0] != '\0')
			i++;
		row = row->next;
	}
	if (count == 0 || i < 3)
		return (-1);
	return (0);
}
int	ft_check_map_lines(t_map_row *row)
{
	int	len;
	int	len_back;
	int	len_next;

	len = 0;
	len_back = 0;
	len_next = 0;
	while (row)
	{
		len = ft_strlen(row->row);
		if (!row->back)
			if (ft_map_strchr(row->row))
				return (-1);
		if (!row->next)
			if (ft_map_strchr(row->row))
				return (-1);
		if (ft_one_of_chr(row->row[0]) || ft_one_of_chr(row->row[len]))
			return (-1);
		if (row->next != NULL)
			len_next = ft_strlen(row->next->row);
		if (row->back != NULL)
		{
			len_back = ft_strlen(row->back->row);
			ft_check_zero_surround(row->row, len_back, len_next);
		}

		row = row->next;
	}
}
