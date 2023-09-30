/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tahaexo <tahaexo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 05:01:57 by msamhaou          #+#    #+#             */
/*   Updated: 2023/09/30 16:01:47 by tahaexo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
				color = 0xFF000000;
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

	double a[2] = {data->player->xpos, data->player->ypos};
	double b[2] = {data->ray[0].nearx, data->ray[0].neary};
	ft_vect_draw(a,b,0xFF,data,data->map->map_img);
	mlx_put_image_to_window(data->mlx, data->win, data->map->map_img->img_ptr, 0,0);

	// ft_draw_player();
}

void	ft_update(t_data *data)
{
	// mlx_destroy_image(data->mlx, data->main_img->img_ptr);
	data->main_img = ft_img_init(data);
	// ft_draw_map(data);
	// ft_draw_player();
}
