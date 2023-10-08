/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tahaexo <tahaexo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:24:33 by msamhaou          #+#    #+#             */
/*   Updated: 2023/10/08 19:31:23 by tahaexo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



double	*ft_hypo_calc(double *a, double *b, t_data *data)
{
	double	*hypo;
	double	x;
	double	y;
	// double	deg;

	x = fabs(b[0] - a[0]);
	y = b[1] - a[1];

	hypo = c_malloc(sizeof(double) * 2, &data->col);
	hypo[0] = sqrt((x * x) + (y * y));
	hypo[1] = asin(y / hypo[0]);

	return (hypo);
}
void	ft_vect_draw(double *a, double *b, int color, t_data *data, t_img *img)
{
	double	i;
	double	*hypo;
	double	*hypo_max;
	double	x;
	double	y;

	i = 0;
	hypo = ft_hypo_calc(a, b, data);

	x = 0;
	y = 0;
	while (i < hypo[0])
	{
		if ((int)a[0] + x > 0 && (int)a[0] + x < WIDTH &&  (int)a[1] + y > 0 && (int)a[1] + y < HEIGHT)
			ft_put_pix(img,(int)a[0] + x, (int)a[1] + y, color, data);

		x += cos(hypo[1]);
		y += sin(hypo[1]);
		i++;
	}
}

double	ft_player_ray_hypo()
{

}

void	ft_draw_ray_vertical(t_data *data, t_player *player, t_ray ray)
{
	double	x,y;
	double	i = 0;
	double	hypo;

	x = 0;
	y = 0;
	hypo = ((player->xpos - ray.v_x) * (player->xpos - ray.v_x)) \
				+ ((player->ypos - ray.v_y) * (player->ypos - ray.v_y));
	hypo = sqrt(hypo);
	while (i < hypo)
	{
		if ((player->ypos + y < 0 )|| (player->ypos + y >( data->map->ymap * (int)GRID)) || \
			(player->xpos + x < 0 )|| (player->xpos + x > data->map->xmap * (int)GRID))
			break;
		ft_put_pix(data->map->map_img, data->player->xpos + x, data->player->ypos + y, \
			0xFF, data);
		x += cos(ray.angle);
		y += sin(ray.angle);
		i++;
	}
}

void	ft_draw_ray_horizontal(t_data *data, t_player *player, t_ray ray)
{
	double	x,y;
	double	i = 0;
	double	hypo;

	x = 0;
	y = 0;
	hypo = ((player->xpos - ray.h_x) * (player->xpos - ray.h_x)) \
				+ ((player->ypos - ray.h_y) * (player->ypos - ray.h_y));
	hypo = sqrt(hypo);
	while (i < hypo)
	{

		if ((player->ypos + y < 0 )|| (player->ypos + y >( data->map->ymap * (int)GRID)) || \
			(player->xpos + x < 0 )|| (player->xpos + x > data->map->xmap * (int)GRID))
			break;
		ft_put_pix(data->map->map_img, data->player->xpos + x, data->player->ypos + y, \
			0xFF0000, data);
		x += cos(ray.angle);
		y += sin(ray.angle);
		i++;
	}
}



void	ft_swap_vect(t_vertex **a, t_vertex **b)
{
	t_vertex	**tmp;

	tmp = a;
	*a = *b;
	*b = *tmp;
}
