/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:14:24 by msamhaou          #+#    #+#             */
/*   Updated: 2023/08/08 15:41:24 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_find_map(int fd, t_collector **col);

bool	ft_one_of_chr(char c)
{
	return(c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '0');
}

int	ft_map_component_find(char c)
{
	if (c == '1')
		return (1);
	if (c == 'N')
		return (8);
	if (c == ' ' || c == '\n')
		return (2);
	return (0);
}

char	*ft_gstrdup(const char *s1, t_collector **col)
{
	void	*ptr;

	ptr = c_malloc(ft_strlen(s1) + 1, col);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s1, ft_strlen(s1) + 1);
	return (ptr);
}

int	ft_max(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}

int	ft_valid_c(char c)
{
	if (c != '0' && c!= '1' && c != 'N' \
			&& c != 'W' && c != 'S' && c != 'E' && c != '\n')
		return (0);
	return (1);
}

int	ft_valid(const char *line)
{
	while (*line)
		if (!ft_valid_c(*(line++)))
			return (0);
	return (1);
}


char	*ft_split_space(const char *str, t_collector **col)
{
	char	*s;
	char	*tmp;
	char	*ret;
	int		i;

	if (!str)
		return (NULL);
	s = (char *)str;
	while (*s && *s != ' ')
		s++;
	while (*s && *s == ' ')
		s++;
	i = 0;
	while (s[i])
		i++;
	ret = c_malloc((sizeof(char) * (i + 1)), col);
	ft_strlcpy(ret, s, i + 1);
	return (ret);
}

int	ft_kamas_count(const char *str)
{
	char	*s;
	int		count;

	s = (char *)str;
	count = 0;
	while (*s)
	{
		if (*s == ',')
			count++;
		if (*(s++) == '-')
			return (-1);
	}
	return (count);
}

void	ft_set_color_check(char *str, t_collector **col)
{
	int	i;
	int	check;

	check = ft_kamas_count(str);
	if (check > 2 || check == -1)
		ft_free_error_type(col, 5);
}

int	ft_set_color(char *str, t_collector **col)
{
	char	**split;
	int		res;

	ft_set_color_check(str, col);
	split = ft_gsplit(str, ',', col);
	res = color_code(ft_gatoi(split[0], col), ft_gatoi(split[1], col), ft_gatoi(split[2], col));
	return (res);
}

int	ft_line_is_spaces(const char *str)
{
	char	*s;

	s = (char *)str;
	while (*s)
		if (*(s++) != ' ')
			return (0);
	return (1);
}

int	ft_line_cases(t_data *data, char *line, int *count)
{
	if (!line)
		ft_free_error_type(&data->col, 4);
	if (!ft_strncmp(line, "NO ", ft_strlen("NO "))){
		data->files_arr[0] = ft_split_space(line, &data->col);
		count[0] += 1;
		}
	else if (!ft_strncmp(line, "SO ", ft_strlen("SO "))){
		data->files_arr[1] = ft_split_space(line, &data->col);
		count[1] += 1;
		}
	else if (!ft_strncmp(line, "WE ", ft_strlen("WE "))){
		data->files_arr[2] = ft_split_space(line, &data->col);
		count[2] += 1;
		}
	else if (!ft_strncmp(line, "EA ", ft_strlen("EA "))){
		data->files_arr[3] = ft_split_space(line, &data->col);
		count[3] += 1;
		}
	else if (!ft_strncmp(line, "F ", ft_strlen("F "))){
		data->files_arr[4] = ft_split_space(line, &data->col);
		count[4] += 1;
		}
	else if (!ft_strncmp(line, "C ", ft_strlen("C "))){
		data->files_arr[5] = ft_split_space(line, &data->col);
		count[5] += 1;
		}
	else if (line[0] == '\0' || ft_line_is_spaces(line))
		return (1);
	else
		ft_free_error_type(&data->col, 4);
	return (0);
}

void	ft_open_xpm(char **files)
{
	int	i;
	int	fd;

	i = 0;
	while (i < 4)
	{
		fd = open(files[i++], O_RDONLY);
		if (fd == -1)
		{
			perror("");
			exit(1);
		}
		close(fd);
	}
}

void	ft_repeat_check(t_data *data, int *count)
{
	int	i;

	i = 0;
	while (i < data->number_of_files)
	{
		if (count[i] == 2 || count[i] == 0)
			ft_free_error_type(&data->col, 4);
		i++;
	}
}

/*get xpm file and color strings*/
void	ft_get_xpm_files_colors(t_data *data, int fd, t_collector **col)
{
	char *line;
	int	i;
	static int	count[7];

	data->files_arr = c_malloc(sizeof(char *) * (7), col);
	i = 0;
	while (i < data->number_of_files)
	{
		line = gnl(fd, col);
		if (ft_line_cases(data, line, count))
			continue;
		i++;
	}
	ft_repeat_check(data, count);
	data->files_arr[i] = NULL;
	ft_open_xpm(data->files_arr);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if(s1[i] != s2[i])
			return (1);
		i++;
	}
	return(0);
}

void	ft_check_file_name(char *filename, t_collector **col)
{
	int	len;
	char *s;

	len = ft_strlen (filename);
	s = ft_gsubstr(filename, len - 4, len, col);
	if (ft_strcmp(s, ".cub") != 0)
		ft_free_error_type(col, 3);
}

int	ft_open_file(char *filename, t_collector **col)
{
	int	fd;

	ft_check_file_name(filename, col);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("");
		ft_free_error_type(col, 20);
	}
	return (fd);
}
void	ft_get_colors(t_data *data, int fd)
{
	data->floor_color = ft_set_color(data->files_arr[4], &data->col);
	data->ciel_color = ft_set_color(data->files_arr[5], &data->col);
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

int	ft_check_zero_surround(char	*row, int back, int	next)
{
	int	i;

	i = 1;
	while (row[i])
	{
		if (row[i] == '0')
		{
			if (i > back || i > next)
				return (-1);
			
		}
		i++;
	}
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

void	ft_link_back(t_map_row *row)
{
	t_map_row	*tmp;

	while (row->next)
	{
		row->next->back = row;
		row = row->next;
	}
}

void	ft_map(t_data *data, char *filename,int fd)
{
	char	*line;

	line = ft_find_map(fd, &data->col);
	data->map->map_compo =  ft_get_map_compo(line, fd, &data->col);
	if (ft_check_map_compo(data->map->map_compo) == -1)
		ft_free_error_type(&data->col, 4);
	ft_link_back(data->map->map_compo);
	if (ft_check_map_lines(data->map->map_compo) == -1)
		ft_free_error_type(&data->col, 4);
}

int	ft_parse(char *filename, t_data *data)
{
	int	fd;

	fd = ft_open_file(filename, &data->col);
	ft_get_xpm_files_colors(data, fd, &data->col);
	ft_get_colors(data, fd);
	ft_map(data, filename, fd);
	return (0);
}
