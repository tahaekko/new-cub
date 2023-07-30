/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:09:02 by msamhaou          #+#    #+#             */
/*   Updated: 2023/07/29 02:40:08 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	foo()
{
	system("leaks Cub3D");
}

void	ft_free_all(t_data *data)
{
	if (data->map)
		free(data->map);
	if (data->main_img->addr)
		free(data->main_img->addr);
	if (data->main_img)
		free(data->main_img);
	if (data->files_arr)
		ft_free_strings(data->files_arr);
	if (data->texture)
		ft_free_strings(data->texture);
	if (data->player)
		free(data->player);
	if (data->ray)
		free(data->ray);
	if (data)
		free(data);
}
int	ft_exit(t_data * data)
{
	exit(0);
	return(1);
}

int	ft_key_press(int key, t_data *data)
{
	if (key == ESC){
		exit(0);
	}
	printf("%d\n", key);
	return (0);
}

int	ft_hooks(t_data	*data)
{
	mlx_hook(data->win, 02,  1L<<0, ft_key_press, data);
	mlx_hook(data->win, 17, 0L, ft_exit, data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;

	// atexit(foo);
	if (!av[1])
		exit(1);
	data = ft_init(av[1]);
	mlx_loop_hook(data->mlx, ft_hooks, data);
	mlx_loop(data->mlx);
}
