/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tahaexo <tahaexo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:45:52 by msamhaou          #+#    #+#             */
/*   Updated: 2023/10/08 19:30:57 by tahaexo          ###   ########.fr       */
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
		data->ray[i].up = (ang > (double)PI && ang < (2 * (double)PI));
		data->ray[i].right = !(ang < (3 * ((double)PI / 2))) && (ang > ((double)PI / 2));
		i++;
	}

}

void	ft_horizontal_intersect(t_data *data, int i)
{
	t_ray	*ray;
	double	offsetx, offsety;

	ray = data->ray;

	ray[i].h_y = ray[i].neary;
	ray[i].h_x = data->player->xpos + (-(2 * ray[i].up - 1)) * (fabs(data->player->ypos - ray[i].h_y) / tan(ray[i].angle));

	offsety = -(2 * ray[i].up - 1) * (double)GRID;
	offsetx = offsety / tan(ray[i].angle);

	while(((int)ray[i].h_y  / (int)GRID) > -1 && (int)ray[i].h_y  / (int)GRID < data->map->ymap&& \
				((int)ray[i].h_x  / (int)GRID) > -1 && (int)ray[i].h_x  / (int)GRID < data->map->xmap &&\
					data->map->map_arr[(int)ray[i].h_y  / (int)GRID][(int)ray[i].h_x / (int)GRID] == '0')
	{
		ray[i].h_y += offsety;
		ray[i].h_x += offsetx;
	}
}

void	ft_vertical_intersect(t_data *data, int i)
{
	t_ray	*ray;
	double	offsetx, offsety;

	ray = data->ray;

	ray[i].v_x = ray[i].nearx;
	ray[i].v_y = data->player->ypos + (2 * ray[i].right - 1) * (fabs(data->player->xpos - ray[i].v_x) * tan(ray[i].angle));
	offsetx = (2 * ray[i].right - 1) * (double)GRID;
	offsety = tan(ray[i].angle) * offsetx;
	while(((int)ray[i].v_y  / (int)GRID) > -1 && (int)ray[i].v_y  / (int)GRID < data->map->ymap&& \
				((int)ray[i].v_x  / (int)GRID) > -1 && (int)ray[i].v_x  / (int)GRID < data->map->xmap &&\
					data->map->map_arr[(int)ray[i].v_y  / (int)GRID][(int)ray[i].v_x / (int)GRID] == '0')
	{
			ray[i].v_x += offsetx;
			ray[i].v_y += offsety;
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
		ray[i].neary = (double)((int)(data->player->ypos / (double)GRID) * (int)GRID) + (-(2*ray[i].up - 1) * 0.0001) + (!(ray[i].up) * GRID);
		ray[i].nearx = ((int)(data->player->xpos / (double)GRID) * (double)GRID) + (ray[i].right * GRID) + ((2 * ray[i].right - 1) *0.0001);
		ft_horizontal_intersect(data, i);
		ft_vertical_intersect(data, i);
		double vertical[] = {ray[i].v_x, ray[i].v_y};
		double horizontal[] = {ray[i].h_x, ray[i].h_y};
		double pp[] = {data->player->xpos, data->player->ypos};
		if (ft_hypo_calc(pp, vertical, data)[0] < ft_hypo_calc(pp, horizontal, data)[0])
			ray[i].is_vertical = 1;
		else
			ray[i].is_vertical = 0;
		i++;
	}
}
