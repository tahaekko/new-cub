/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:42:21 by msamhaou          #+#    #+#             */
/*   Updated: 2023/07/30 07:04:34 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_mlx_init(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		exit(1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "ZEB!");
}

t_img	*ft_img_init(t_data *data)
{
	t_img	*img;

	img = ft_img_alloc();
	ft_set_img(img, WIDTH, HEIGHT, data);
	return (img);
}

t_map	*ft_map_init(t_data *data)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->xmap = 0;
	map->ymap = 0;
	map->off_map = (int)GRID;
	map->map_compo = NULL;
	return (map);
}
int	ft_get_player_y(t_data *data)
{
	int	y;

	y = 0;
	while (data->map->map_compo[y])
	{
		if (ft_strchr(data->map->map_compo[y], 'N'))
			return(y);
		y++;
	}
	return (0);
}

int	ft_get_player_x(t_data *data, int ypos)
{
	int	x;

	x = 0;
	while (data->map->map_compo[ypos][x] != 'N')
		x++;
	return (x);
}

t_player	*ft_init_player(t_data *data)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	player->height = 0;
	player->width = 0;
	player->ypos = ft_get_player_y(data);
	player->xpos = ft_get_player_x(data, player->ypos);
	printf("%f\n", player->xpos);
	player->xrot = 0;
	player->yrot = 0;
	player->angle = 0;
	return (player);
}

t_vertex	*ft_vertex()
{
	t_vertex *vertex;

	vertex = malloc(sizeof(t_vertex));
	vertex->x = 0;
	vertex->y = 0;
	return (vertex);
}

t_ray	*ft_ray_init()
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	ray->hit_point_h = ft_vertex();
	ray->hit_point_v = ft_vertex();
	ray->angle = 0;
	return (ray);
}

char	**ft_chars_alloc(int num)
{
	char	**files;

	files = malloc(sizeof(char *) * (num + 1));
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

void	ft_leaks_add(t_data *data)
{
	printf("file %p\n", data->files_arr);
	printf("texture %p\n", data->texture);
	printf("img %p\n", data->main_img);
	printf("map %p\n", data->map);
	printf("player %p\n", data->player);
	printf("ray %p\n", data->ray);
	printf("mlx %p\n", data->mlx);
	printf("win %p\n", data->win);

}

t_img	ft_get_texture_img(t_data *data, char *file)
{
	int	x;
	int y;
	void	*p;
	t_img	texture;

	x = 0;
	y = 0;
	// texture = malloc(sizeof(t_img));
	p = mlx_xpm_file_to_image(data->mlx, file, &x, &y);
	texture.addr = mlx_get_data_addr(p, &texture.bpp, &texture.line, &texture.endian);
	return (texture);
}

t_img	*ft_init_textures(t_data *data)
{
	int i;
	t_img	*texture;

	texture = malloc(sizeof(t_img) * 4);
	i = 0;
	while (i < 4)
	{
		texture[i] = ft_get_texture_img(data, data->files_arr[i]);
		i++;
	}
	return (texture);
}

t_data	*ft_init(char *filename)
{
	t_data *data;

	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		exit(1);
	data->number_of_files = 6;
	ft_nullafy(data);
	data->files_arr = ft_chars_alloc(data->number_of_files);
	data->map = ft_map_init(data);
	ft_parse(filename, data);
	ft_mlx_init(data);
	data->texture = ft_init_textures(data);
	data->main_img = ft_img_init(data);
	data->player = ft_init_player(data);
	data->ray = ft_ray_init();
	ft_leaks_add(data);
	ft_draw_init(data);
	return (data);
}
