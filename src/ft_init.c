/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tahaexo <tahaexo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:42:21 by msamhaou          #+#    #+#             */
/*   Updated: 2023/09/30 04:26:11 by tahaexo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_mlx_init(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		ft_free_error_type(&data->col, 0);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "ZEB!");
}

t_img	*ft_img_init(t_data *data)
{
	t_img	*img;

	img = ft_img_alloc(data);
	ft_set_img(img, WIDTH, HEIGHT, data);
	return (img);
}

t_map	*ft_map_init(t_data *data)
{
	t_map	*map;

	map = c_malloc(sizeof(t_map), &data->col);
	map->xmap = 0;
	map->ymap = 0;
	map->off_map = (int)GRID;
	map->map_compo = NULL;

	return (map);
}
double	ft_get_player_y(t_data *data)
{
	double	y;

	y = 0;
	while (data->map->map_compo)
	{
		if (ft_strchr(data->map->map_compo->row, data->orient_identifier))
			return(y);
		data->map->map_compo = data->map->map_compo->next;
		y++;
	}
	return (0);
}

double	ft_get_player_x(t_data *data, int ypos)
{
	int	x;

	x = 0;
	while (data->map->map_compo)
	{
		x = 0;
		while (data->map->map_compo->row[x])
		{
			if (data->map->map_compo->row[x] == data->orient_identifier)
				return (x);
			x++;
		}
		data->map->map_compo = data->map->map_compo->next;
	}
	return (0);
}

void	ft_map_img_init(t_data *data)
{
	t_map *map;

	map = data->map;
	map->map_img = ft_img_alloc(data);
	ft_set_img(map->map_img,WIDTH,HEIGHT,data);
	for (int i = 0; i < HEIGHT ; i++)
		for (int j = 0; j < WIDTH ; j++)
			ft_put_pix(map->map_img, j, i, 0x00FFFFFF, data);
}

double	ft_get_angle(t_data *data)
{
  char	orient;

  orient = data->orient_identifier;
  if (orient == 'N')
    return (270);
  else if (orient == 'S')
    return (90);
  else if (orient == 'W')
    return (180);
  return (0);
}

t_player	*ft_init_player(t_data *data)
{
	t_player *player;

	player = c_malloc(sizeof(t_player), &data->col);
	player->height = 5;
	player->width = 5;
	player->ypos = (double)ft_get_player_y(data) * (double)GRID;
	player->xpos = (double)ft_get_player_x(data, player->ypos) * (double)GRID;
	player->angle = ft_get_angle(data) * (double)(DEG_TO_RAD);
	player->xrot = cos(player->angle);
	player->yrot = sin(player->angle);

	return (player);
}

t_vertex	*ft_vertex(t_collector **col)
{
	t_vertex *vertex;

	vertex = c_malloc(sizeof(t_vertex), col);
	vertex->x = 0;
	vertex->y = 0;
	return (vertex);
}

t_ray	*ft_ray_init(t_collector **col)
{
	t_ray	*ray;
	int		i;

	i = 0;
	ray = (t_ray *)c_malloc(sizeof(t_ray) * (int)WIDTH, col);
	while (i < (int)WIDTH)
	{
		ray[i].h_x = 0;
		ray[i].h_y = 0;
		ray[i].v_x = 0;
		ray[i].v_y = 0;
		ray[i].length = 0;
		ray[i++].angle = 0;
	}
	return (ray);
}

char	**ft_chars_alloc(int num, t_collector **col)
{
	char	**files;

	files = c_malloc(sizeof(char *) * (num + 1), col);
	return (files);
}
void	ft_nullafy(t_data *data)
{
	data->files_arr = NULL;
	data->texture = NULL;
	data->main_img = NULL;
	data->map = NULL;
	data->player = NULL;
	data->ray = NULL;
}

t_img	ft_get_texture_img(t_data *data, t_img *texture, char *file)
{
	int	x;
	int y;
	void	*p;

	x = 0;
	y = 0;
	p = mlx_xpm_file_to_image(data->mlx, file, &x, &y);
	texture->addr = mlx_get_data_addr(p, &texture->bpp, &texture->line, &texture->endian);
	return (*texture);
}

t_img	*ft_init_textures(t_data *data)
{
	int i;
	t_img	*texture;

	texture = c_malloc(sizeof(t_img) * 4, &data->col);
	i = 0;
	while (i < 4)
	{
		texture[i] = ft_get_texture_img(data, &texture[i], data->files_arr[i]);
		i++;
	}
	return (texture);
}


t_data	*ft_init(char *filename)
{
	t_data *data;
	t_collector **col = malloc(sizeof(t_collector *));
	data = NULL;

	*col = NULL;
	data = c_malloc(sizeof(t_data), col);
	data->col = *col;
	data->number_of_files = 6;
	ft_nullafy(data);
	data->files_arr = ft_chars_alloc(data->number_of_files, &data->col);
	data->map = ft_map_init(data);
	ft_parse(filename, data);
	ft_mlx_init(data);
	data->texture = ft_init_textures(data);
	data->main_img = ft_img_init(data);
	data->player = ft_init_player(data);
	data->ray = ft_ray_init(&data->col);
	ft_map_img_init(data);
	ft_calculat_ray_angles(&data->player->angle, data->ray);
	ft_calculate_ray_dir(data);
	ft_calculate(data);
	data->key_pressed = c_malloc(sizeof(int) * 6, &data->col);
	ft_draw_init(data);
	return (data);
}
