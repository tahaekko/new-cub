/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tahaexo <tahaexo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:45:52 by msamhaou          #+#    #+#             */
/*   Updated: 2023/10/08 19:22:19 by tahaexo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_debug(t_data *data)
{

}

void	ft_calculat_ray_angles(double *player_ang, t_ray *ray)
{
	int i;
	double angle_steps;
	double	ang_init;

	ang_init= *player_ang - (double)((double)FOV/2)* (double)DEG_TO_RAD;
	angle_steps = (double)((double)FOV / (double)WIDTH) * (double)DEG_TO_RAD;
	i = 0;
	while (i < WIDTH)
	{
		if (ang_init > (double)(2 * (double)PI))
			ang_init -= (double)(2 * (double)PI);
		else if (ang_init < 0)
			ang_init+= (double)(2 * (double)PI);
		ray[i].angle = ang_init;
		ang_init+=angle_steps;
		i++;
	}
}
void	ft_calculate_ray_dir(t_data *data)
{
	int	i;
	double	ang;

	i = 0;
	while (i < (int)WIDTH)
	{
		ang = data->ray[i].angle;
		if (ang > 0 && ang < (double)PI)
			data->ray[i].up = 0;
		else if (ang > (double)PI && ang < (2 * (double)PI))
			data->ray[i].up = 1;
		else
			data->ray[i].up = -1;
		if (((ang > 0) && (ang < ((double)PI / 2))) || \
			((ang < (2 * (double)PI)) && (ang > (3 * ((double)PI / 2)))))
			data->ray[i].right = 1;
		else if (((ang < (3 * ((double)PI / 2))) && (ang > ((double)PI / 2))))
			data->ray[i].right = 0;
		else
			data->ray[i].right = -1;
		i++;
	}

}

void	ft_calculate(t_data *data)
{
	t_ray	*ray;
	int		i;
	double	nearx, neary;

	ray = data->ray;
	i = 0;
	while (i < (int)WIDTH)
	{
		if (ray[i].up == 1)
			neary = (double)((int)(data->player->ypos / (double)GRID) * (int)GRID) - 0.0001;
		else
			neary = (double)((int)(data->player->ypos / (double)GRID) * (int)GRID) + (double)GRID+  0.0001;
		if (ray[i].right)
			nearx = ((int)(data->player->xpos / (double)GRID) * (double)GRID) + (double)GRID + 0.0001;
		else
			nearx = ((int)(data->player->xpos / (double)GRID) * (double)GRID) - 0.0001;
		ray[i].nearx = nearx;
		ray[i].neary = neary;

		ray[i].h_y = ray[i].neary;
		if (ray[i].up)
			ray[i].h_x = data->player->xpos - (fabs(data->player->ypos - ray[i].h_y) / tan(ray[i].angle));
		else
			ray[i].h_x = data->player->xpos + (fabs(data->player->ypos - ray[i].h_y) / tan(ray[i].angle));

		ray[i].v_x = nearx;
		if (ray[i].right)
			ray[i].v_y = data->player->ypos + (fabs(data->player->xpos - ray[i].v_x) * tan(ray[i].angle));
		else
			ray[i].v_y = data->player->ypos - (fabs(data->player->xpos - ray[i].v_x) * tan(ray[i].angle));


		while(((int)ray[i].v_y  / (int)GRID) > -1 && (int)ray[i].v_y  / (int)GRID < data->map->ymap&& \
					((int)ray[i].v_x  / (int)GRID) > -1 && (int)ray[i].v_x  / (int)GRID < data->map->xmap &&\
						data->map->map_arr[(int)ray[i].v_y  / (int)GRID][(int)ray[i].v_x / (int)GRID] == '0')
		{
			if (ray[i].right)
			{
				ray[i].v_x += (double)GRID;
				ray[i].v_y += tan(ray[i].angle) * (double)GRID;
			}
			else
			{
				ray[i].v_x -= (double)GRID;
				ray[i].v_y -= tan(ray[i].angle) * (double)GRID;
			}
		}

		int j = 0;
		while(((int)ray[i].h_y  / (int)GRID) > -1 && (int)ray[i].h_y  / (int)GRID < data->map->ymap&& \
					((int)ray[i].h_x  / (int)GRID) > -1 && (int)ray[i].h_x  / (int)GRID < data->map->xmap &&\
						data->map->map_arr[(int)ray[i].h_y  / (int)GRID][(int)ray[i].h_x / (int)GRID] == '0')
		{
			if (ray[i].up)
			{
				ray[i].h_y -= (double)GRID;
				ray[i].h_x -= (double)GRID / tan(ray[i].angle);
			}
			else
			{
				ray[i].h_y += (double)GRID;
				ray[i].h_x += (double)GRID / tan(ray[i].angle);
			}
			j++;
		}

		double vertical[] = {ray[i].v_x, ray[i].v_y};
		double horizontal[] = {ray[i].h_x, ray[i].h_y};
		double pp[] = {data->player->xpos, data->player->ypos};
		if (ft_hypo_calc(pp, vertical)[0] < ft_hypo_calc(pp, horizontal)[0])
			ray[i].is_vertical = 1;
		else
			ray[i].is_vertical = 0;
		i++;
	}
}
