/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tahaexo <tahaexo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:09:02 by msamhaou          #+#    #+#             */
/*   Updated: 2023/09/25 05:58:04 by tahaexo          ###   ########.fr       */
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
	mlx_destroy_image(data->mlx, data->texture->img_ptr);
	ft_free_addr(data->col);
	// ft_free_collector(data->col);
	exit(0);
}

int	ft_exit(t_data * data)
{
	ft_free_all(data);
	return(1);
}

int ft_hook(int key, void *param)
{
	t_data *data = (t_data *)param;
	if (key == ESC)
		ft_exit(data);
	("%d\n", key);
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
	mlx_key_hook(data->win, ft_hook, data);
	mlx_loop(data->mlx);
}
