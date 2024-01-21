/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tahaexo <tahaexo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 05:01:57 by msamhaou          #+#    #+#             */
/*   Updated: 2023/10/17 15:39:33 by tahaexo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_wall(t_data *data)
{
	int	y = 0;
	int i = 0;
	int start;
	int	x_hit_poit_each_grid, y_hit_poit_each_grid, color;
	int	x_texture, y_texture;

	while (i < WIDTH)
	{
		start = ((int)HEIGHT / 2) - (data->ray[i].wall/2);
		x_hit_poit_each_grid = !(data->ray[i].is_vertical) * (int)(data->ray[i].h_x) % (int)GRID  + \
								data->ray[i].is_vertical * ((int)(data->ray[i].v_y) % (int)GRID);
		x_texture = (x_hit_poit_each_grid * (data->ray[i].texture.line /  (data->ray[i].texture.bpp / 8))) / (int)GRID;
		y = 0;
		while (y < data->ray[i].wall)
		{
			if (y + start < 0 || y + start > HEIGHT)
			{
				y++;
				continue;
			}
			y_texture = (y * (int)GRID) / data->ray[i].wall;
			color = *((int *)(data->ray[i].texture.addr) + ((y_texture * (data->ray[i].texture.line / 4)) + x_hit_poit_each_grid));
			ft_put_pix(data->map->map_img, i,y + start,color,data);
			y++;
		}
		i++;
	}
}

void	ft_draw_grid(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map->off_map)
	{
		j = 0;
		while (j < data->map->off_map)
		{
			if ((j + 1) == data->map->off_map || (i + 1) == data->map->off_map)
				ft_put_pix(data->map->map_img, x + j++, y + i, 0, data);
			else
				ft_put_pix(data->map->map_img, x + j++, y + i, color, data);
		}
		i++;
	}
}

void	ft_draw_map(t_data *data)
{
	int	i;
	int	j;
	int	color;

	i = 0;

	while (data->map->map_arr[i])
	{
		j = 0;
		while (data->map->map_arr[i][j])
		{
			color = (int)FLOOR;
			if (data->map->map_arr[i][j] == '1')
				color = (int)WALL;
			else if (data->map->map_arr[i][j] != '0' )
				color = 0x00FFFFFF;
			ft_draw_grid(data, data->map->off_map * j, data->map->off_map * i, color);
			j++;
		}
		i++;
	}
}

void	ft_draw_dir(t_data *data, int x, int y, int color)
{
	//player pos to len

	// while
}

void	ft_draw_player(t_data *data)
{
	t_player	*player;
	double i;
	double	j;

	player = data->player;
	i = 0;
	while (i < player->height)
	{
		j = 0;
		while (j < player->width)
		{
			ft_put_pix(data->map->map_img, (player->x_inmap) + (j++) - ((double)player->width / 2), \
				(player->y_inmap) + i - ((double)player->height / 2), 0xFF00FF, data);
		}
		i++;
	}
	// mlx_put_image_to_window(data->mlx, data->win, data->map->map_img->img_ptr, 0,0);

	// ft_draw_dir();
}


void	ft_draw_sky(t_data *data)
{
	for (int i = 0; i < (int)HEIGHT / 2; i++)
		for (int j = 0; j < (int)WIDTH; j++)
			ft_put_pix(data->map->map_img, j,i,data->ciel_color,data);
}

void	ft_draw_floor(t_data *data)
{
	for (int i = (int)HEIGHT / 2; i < (int)HEIGHT; i++)
		for (int j = 0; j < (int)WIDTH; j++)
			ft_put_pix(data->map->map_img, j,i,data->floor_color,data);
}
void	ft_draw_init(t_data *data)
{
	// ft_draw_map(data);
	// ft_draw_player(data);
	// ft_draw_debug(data, 1);
	ft_draw_sky(data);
	ft_draw_floor(data);
	ft_draw_wall(data);
	// exit(1);
	mlx_put_image_to_window(data->mlx, data->win, data->map->map_img->img_ptr, 0,0);
}

void	ft_update(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	ft_draw_sky(data);
	ft_draw_floor(data);
	// ft_draw_map(data);
	// ft_draw_player(data);
	// ft_draw_debug(data, 1);
	ft_draw_wall(data);
	mlx_put_image_to_window(data->mlx, data->win, data->map->map_img->img_ptr, 0,0);

}
