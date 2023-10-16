/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tahaexo <tahaexo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:09:02 by msamhaou          #+#    #+#             */
/*   Updated: 2023/10/16 02:44:18 by tahaexo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	foo()
{
	system("leaks Cub3D");
}

void	ft_free_all(t_data *data)
{
	printf("point %p\n", data->col);
	t_collector **col = data->coll;
	// mlx_destroy_image(data->mlx, data->texture->img_ptr);
	ft_free_addr(data->col);
	ft_free_collector(data->col);
	free(col);
	exit(0);
}

int	ft_exit(t_data * data)
{
	ft_free_all(data);
	return(1);
}

int ft_tst(int key, void *param)
{
	t_data *data = (t_data *)param;
	if (key == ESC)
		ft_exit(data);
	data->player->angle += ((key == KEY_RG) + (key == KEY_LE) * (-1)) * 0.08;
	data->player->angle -= (data->player->angle > (2 * (double)PI)) * (2 * (double)PI);
	data->player->angle += (data->player->angle < 0) * (2 * (double)PI);
	if (data->map->map_arr[(int)(data->player->ypos + ((((key == KEY_W) + (-1 * (key == KEY_S))) * (sin(data->player->angle))) * (int)(GRID * 0.2)))/(int)GRID]\
		[(int)(data->player->xpos + (((key == KEY_W) + (-1 * (key == KEY_S))) * (cos(data->player->angle)) * (int)(GRID * 0.2))) / (int)GRID] != '1')
	{
		data->player->xpos += ((key == KEY_W) + (-1 * (key == KEY_S))) * (cos(data->player->angle)) * data->player->speed;
		data->player->ypos += ((key == KEY_W) + (-1 * (key == KEY_S))) * (sin(data->player->angle)) * data->player->speed;
	}
	ft_calculat_ray_angles(&data->player->angle, data->ray);
	ft_calculate_ray_dir(data);
	ft_calculate(data);
	ft_update(data);
	return 0;
}


int	main(int ac, char **av)
{
	t_data	*data;
	t_texture *text;

	// atexit(foo);
	if (!av[1])
		exit(1);
	data = ft_init(av[1]);
	("HEAD1 %p\n", data->col);
	int key;
	mlx_hook(data->win, 02, 1L<<0, ft_tst, data);
	mlx_loop(data->mlx);
}
