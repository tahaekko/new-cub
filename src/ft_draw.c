/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tahaexo <tahaexo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 05:01:57 by msamhaou          #+#    #+#             */
/*   Updated: 2023/10/12 18:58:04 by tahaexo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_wall(t_data *data)
{
	int	y =0;
	int i = 0;
	int start;

	while (i < WIDTH)
	{
		start = ((int)HEIGHT / 2) - (data->ray[i].wall/2);
		y = 0;
		while (y < data->ray[i].wall)
		{
			ft_put_pix(data->map->map_img, i,y + start,0xFF0000,data);
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
			ft_put_pix(data->map->map_img, (player->xpos) + (j++) - ((double)player->width / 2), \
				(player->ypos) + i - ((double)player->height / 2), 0xFF00FF, data);
		}
		i++;
	}
	// mlx_put_image_to_window(data->mlx, data->win, data->map->map_img->img_ptr, 0,0);

	// ft_draw_dir();
}

void	ft_draw_init(t_data *data)
{
	ft_draw_map(data);
	ft_draw_player(data);
	ft_draw_debug(data, 1);
	ft_draw_wall(data);
	mlx_put_image_to_window(data->mlx, data->win, data->map->map_img->img_ptr, 0,0);

	// ft_draw_player();
}

void	set_black_back(t_data *data)
{
	for (int i = 0; i < (int)HEIGHT; i++)
		for (int j = 0; j < (int)WIDTH; j++)
			ft_put_pix(data->map->map_img, j,i,0xFFFFFFFF,data);
}

void	ft_update(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	// mlx_destroy_image(data->mlx, data->map->map_img->img_ptr);
	// data->map->map_img->img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	set_black_back(data);
	ft_draw_map(data);
	ft_draw_player(data);
	ft_draw_debug(data, 1);
	ft_draw_wall(data);
	mlx_put_image_to_window(data->mlx, data->win, data->map->map_img->img_ptr, 0,0);

}
