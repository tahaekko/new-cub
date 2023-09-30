/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tahaexo <tahaexo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:45:52 by msamhaou          #+#    #+#             */
/*   Updated: 2023/09/30 04:26:35 by tahaexo          ###   ########.fr       */
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
			neary = ((data->player->ypos / (double)GRID) * (double)GRID )- 0.0001;
		else
			neary = ((data->player->ypos / (double)GRID) * (double)GRID) + (double)GRID+  0.0001;
		if (ray[i].right)
			nearx = ((data->player->xpos / (double)GRID) * (double)GRID) + (double)GRID + 0.0001;
		else
			nearx = ((data->player->xpos / (double)GRID) * (double)GRID) - 0.0001;
		ray[i].nearx = nearx;
		ray[i].neary = neary;
		printf("%d\n", ray[i].nearx);
		i++;
	}
}
