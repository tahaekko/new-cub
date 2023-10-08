/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tahaexo <tahaexo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:09:02 by msamhaou          #+#    #+#             */
/*   Updated: 2023/10/08 19:19:59 by tahaexo          ###   ########.fr       */
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
	// mlx_destroy_image(data->mlx, data->texture->img_ptr);
	ft_free_addr(data->col);
	// ft_free_collector(data->col);
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
	if (key == KEY_RG)
		data->player->angle += 0.1;
	if (key == KEY_LE)
		data->player->angle -= 0.1;
	if (data->player->angle > (2 * (double)PI))
		data->player->angle -= 2 * (double)PI;
	if (data->player->angle < 0)
		data->player->angle += 2 * (double)PI;
	ft_calculat_ray_angles(&data->player->angle, data->ray);
	ft_calculate_ray_dir(data);
	ft_calculate(data);
	ft_update(data);
	return 0;
}

// int ft_hook(int key, void *param)
// {
// 	t_data *data = (t_data *)param;
// 	if (key == ESC)
// 		ft_exit(data);
// 	if (key == KEY_RG)
// 		data->player->angle += 0.1;
// 	if (key == KEY_LE)
// 		data->player->angle -= 0.1;
// 	if (data->player->angle > (2 * (double)PI))
// 		data->player->angle -= 2 * (double)PI;
// 	if (data->player->angle < 0)
// 		data->player->angle += 2 * (double)PI;
// 	return 0;
// }


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
