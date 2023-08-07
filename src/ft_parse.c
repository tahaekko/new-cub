/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:14:24 by msamhaou          #+#    #+#             */
/*   Updated: 2023/08/07 16:43:30 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_find_map(int fd, t_collector **col);

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

char	**ft_map_fill(int fd, int width, int height, t_collector **col)
{
	char	**res;
	int		i;
	char	*line;

	res = c_malloc(sizeof(char *) * (height + 1), col);
	i = 0;
	line = gnl(fd, col);
	while (line && line[0] != '1')
	{
		line = gnl(fd, col);
	}
	while (line && i < height)
	{
		res[i++] = ft_gstrdup(line, col);
		line = gnl(fd, col);
	}
	res[i] = NULL;
	return (res);
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

int	ft_set_color(char *str, t_collector **col)
{
	char	**split;
	int		res;

	split = ft_gsplit(str, ',', col);
	res = color_code(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]));
	return (res);
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
	else if (line[0] == '\0')
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

char	*ft_gsubstr(char const *s, unsigned int start, size_t len, t_collector **col)
{
	char	*str;

	if (!s)
		return (0);
	if (ft_strlen(s) < start)
	{
		str = c_malloc((1 * sizeof(char)), col);
		*str = '\0';
		return (str);
	}
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	str = c_malloc(((len + 1) * sizeof (char)), col);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
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

void	ft_get_dim(int fd, char *prev_line, t_data *data, t_collector **col)
{
	char	*line;
	t_map	*map;

	map = data->map;
	line = prev_line;
	map->xmap = ft_strlen(line);
	map->ymap = 0;
	while (line)
	{

		line = gnl(fd, col);
		map->ymap++;
		if (!line)
			break;
		if (!ft_valid((const char *)line))
		{
			ft_putendl_fd("Error char", 2);

			exit(1);
		}
		map->xmap = ft_max(map->xmap, ft_strlen(line));
	}

}

char	*ft_find_map(int fd, t_collector **col)
{
	char	*line;

	line = gnl(fd, col);
	while (line[0] == '\0')
	{
		line = gnl(fd, col);
	}
	if (line [0] != '1')
	{
		printf("Err\n");
		// ft_free_addr(*col);
		// ft_free_collector(col);
		exit(1);
	}
	return (line);
}

void	ft_map(t_data *data, char *filename,int fd)
{
	char	*line;
	int		new_fd = 0;

	line = ft_find_map(fd, &data->col);
	ft_get_dim(fd, line , data, &data->col);
	close(fd);
	new_fd = open(filename, O_RDONLY);
	data->map->map_compo = ft_map_fill(new_fd, data->map->xmap, data->map->ymap, &data->col);

}

int	ft_parse(char *filename, t_data *data)
{
	int	fd;

	fd = ft_open_file(filename, &data->col);
	ft_get_xpm_files_colors(data, fd, &data->col);
	ft_get_colors(data, fd);
	printf("%d\n", data->ciel_color);
	ft_map(data, filename, fd);
	return (0);
}
