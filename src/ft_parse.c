/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 20:14:24 by msamhaou          #+#    #+#             */
/*   Updated: 2023/07/30 04:13:31 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_find_map(int fd);

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

char	**ft_map_fill(int fd, int width, int height)
{
	char	**res;
	int		i;
	char	*line;

	res = malloc(sizeof(char *) * (height + 1));
	i = 0;
	line = get_next_line(fd);
	while (line && line[0] != '1')
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line && i < height)
	{
		res[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
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

void	ft_free_strings(char **s)
{
	int	i;

	i = 0 ;
	while (s[i])
		free(s[i++]);
	free(s);
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


char	*ft_split_space(const char *str)
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
	ret = malloc(sizeof(char) * (i));
	ft_strlcpy(ret, s, i);
	return (ret);
}

int	ft_set_color(char *str, char *s)
{
	char	*raw;
	char	**split;
	int		res;

	raw = ft_substr(str, (unsigned int)ft_strlen(s), ft_strlen(str));
	split = ft_split(raw, ',');
	free(raw);
	res = color_code(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]));
	ft_free_strings(split);
	return (res);
}

int	ft_line_cases(t_data *data, char *line)
{
	if (!line)
	{
		ft_putendl_fd("Error!", 2);
		exit(1);
	}
	if (!ft_strncmp(line, "NO ", ft_strlen("NO ")))
		data->files_arr[0] = ft_split_space(line);
	else if (!ft_strncmp(line, "SO ", ft_strlen("SO ")))
		data->files_arr[1] = ft_split_space(line);
	else if (!ft_strncmp(line, "WE ", ft_strlen("WE ")))
		data->files_arr[2] = ft_split_space(line);
	else if (!ft_strncmp(line, "EA ", ft_strlen("EA ")))
		data->files_arr[3] = ft_split_space(line);
	else if (!ft_strncmp(line, "F ", ft_strlen("F ")))
		data->files_arr[4] = ft_split_space(line);
	else if (!ft_strncmp(line, "C ", ft_strlen("C ")))
		data->files_arr[5] = ft_split_space(line);
	else if (line[0] == '\n')
	{
		free(line);
		return (1);
	}
	else
	{
		ft_putendl_fd("Error!", 2);
		exit(1);
	}
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

void	ft_get_xpm_files(t_data *data, int fd)
{
	char *line;
	int	i;

	data->files_arr = malloc(sizeof(char *) * (7));
	i = 0;
	while (i < data->number_of_files)
	{
		line = get_next_line(fd);
		if (ft_line_cases(data, line))
			continue;
		free(line);
		i++;
	}
	data->files_arr[i] = NULL;

	for (int i = 0; data->files_arr[i]; i++)
		printf("%s\n", data->files_arr[i]);
	ft_open_xpm(data->files_arr);
}

int	ft_open(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("");
		exit(1);
	}
	return (fd);
}
void	ft_get_colors(t_data *data, int fd)
{
	int	i;
	char *line;

	i = 0;
	while (i < 2)
	{
		line = get_next_line(fd);
		if (!line)
		{
			ft_putendl_fd("Error!", 2);
			exit(1);
		}
		if (line[0] == '\n')
		{
			free(line);
			continue;
		}
		if (!ft_strncmp(line, "F ", ft_strlen("F "))){

			data->floor_color = ft_set_color(line, "F ");
			}
		else if (!ft_strncmp(line, "C ", ft_strlen("C ")))
			data->ciel_color=  ft_set_color(line, "C ");
		else
		{
			ft_putendl_fd("Error!", 2);
			exit(1);
		}
		free(line);
		i++;

	}
}

void	ft_get_dim(int fd, char *prev_line, t_data *data)
{
	char	*line;
	t_map	*map;

	map = data->map;
	line = prev_line;
	map->xmap = ft_strlen(line);
	map->ymap = 0;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		map->ymap++;
		if (!line)
			break;
		if (!ft_valid((const char *)line))
		{
			ft_putendl_fd("Error char", 2);
			free(line);
			exit(1);
		}
		map->xmap = ft_max(map->xmap, ft_strlen(line));
	}
	free(line);
}

char	*ft_find_map(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	if (line [0] != '1')
	{
		free(line);
		printf("Err\n");
		exit(1);
	}
	return (line);
}

void	ft_map(t_data *data, char *filename,int fd)
{
	char	*line;
	int		new_fd = 0;

	line = ft_find_map(fd);
	ft_get_dim(fd, line , data);
	close(fd);
	new_fd = open(filename, O_RDONLY);
	data->map->map_compo = ft_map_fill(new_fd, data->map->xmap, data->map->ymap);

}

int	ft_parse(char *filename, t_data *data)
{
	int	fd;

	fd = ft_open(filename);
	ft_get_xpm_files(data, fd);
	ft_map(data, filename, fd);
	return (0);
}
