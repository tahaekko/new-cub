/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 05:01:57 by msamhaou          #+#    #+#             */
/*   Updated: 2023/08/08 11:17:51 by msamhaou         ###   ########.fr       */
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
				ft_put_pix(data->main_img, x + j++, y + i, 0, data);
			else
				ft_put_pix(data->main_img, x + j++, y + i, color, data);
		}
		i++;
	}
}

// void	ft_draw_map(t_data *data)
// {
// 	int	i;
// 	int	j;
// 	int	color;

// 	i = 0;
// 	while (i < data->map->ymap)
// 	{
// 		j = 0;
// 		while (j < ft_strlen(data->map->map_compo[i]))
// 		{
// 			color = (int)FLOOR;
// 			if (data->map->map_compo[i][j] == '1')
// 				color = (int)WALL;
// 			else if (data->map->map_compo[i][j] != '0' )
// 				color = 0xFF000000;
// 			ft_draw_grid(data, data->map->off_map * j, data->map->off_map * i, color);
// 			j++;
// 		}
// 		i++;
// 	}
// 	ft_put_main_img(data);
// }

void	ft_draw_init(t_data *data)
{
	// ft_draw_map(data);
	// ft_draw_player(data);
	// ft_draw_player();
}

void	ft_update(t_data *data)
{
	mlx_destroy_image(data->mlx, data->main_img->img_ptr);
	data->main_img = ft_img_init(data);
	// ft_draw_map(data);
	// ft_draw_player();
}
