/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tahaexo <tahaexo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:45:52 by msamhaou          #+#    #+#             */
/*   Updated: 2023/09/26 07:49:15 by tahaexo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_debug(t_data *data)
{

}

void	ft_calculat(t_data *data)
{
	t_ray *rays;
	int i;
	int	num_of_rays;
	double pangle;
	double angle_steps;
	double	fov = (double)FOV;

	rays = data->ray;
	pangle = data->player->angle;
	num_of_rays = (int)WIDTH;
	angle_steps = (double)(fov / (double)num_of_rays) * DEG_TO_RAD;
	double	ang_init = pangle - (fov/2)*DEG_TO_RAD;
	double ang_end = ang_init + (2 * (fov/2)*DEG_TO_RAD);

	printf("%f\n", ang_init);
	printf("%f\n", ang_end);

	i = 0;
	while (i < WIDTH)
	{
		if (ang_init > (double)(2 * (double)PI))
			ang_init -= (double)(2 * (double)PI);
		if (ang_init < 0)
			ang_init+= (double)(2 * (double)PI);
		rays[i].angle = ang_init;
		ang_init+=angle_steps;
		i++;
	}
	printf("%f\n",rays[i-1].angle);
	printf("%f\n",rays[0].angle);

}
