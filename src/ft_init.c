/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:42:21 by msamhaou          #+#    #+#             */
/*   Updated: 2023/07/30 04:05:32 by msamhaou         ###   ########.fr       */
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
	map->off_map = 0;
	map->map_compo = NULL;
	return (map);
}

t_player	*ft_init_player()
{
	t_player *player;

	player = malloc(sizeof(t_player));
	player->height = 0;
	player->width = 0;
	player->xpos = 0;
	player->ypos = 0;
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
	data->texture = ft_chars_alloc(data->number_of_files);
	data->map = ft_map_init(data);
	ft_parse(filename, data);
	ft_mlx_init(data);
	// exit(1);
	data->main_img = ft_img_init(data);
	data->player = ft_init_player();
	data->ray = ft_ray_init();
	ft_leaks_add(data);
	return (data);
}
