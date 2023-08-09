/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:09:02 by msamhaou          #+#    #+#             */
/*   Updated: 2023/08/09 15:34:35 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	foo()
{
	system("leaks Cub3D");
}

void	ft_free_all(t_data *data)
{
	ft_free_addr(data->col);
	ft_free_collector(&data->col);
	exit(0);
}

int	ft_exit(t_data * data)
{
	ft_free_all(data);
	return(1);
}

int	ft_key_press(int key, t_data *data)
{
	if (key == ESC){
		exit(0);
	}
	printf("%d\n", key);
	if (key == KEY_W)
		ft_update(data);
	return (0);
}

static void	ft_hooks(void	*param)
{
	t_data *data;

	data = (t_data *)param;
	// mlx_hook(data->win, 02,  1L<<0, ft_key_press, data);
	// mlx_hook(data->win, 17, 0L, ft_exit, data);
	// return (0);
	// return (NULL);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_texture *text;

	atexit(foo);
	if (!av[1])
		exit(1);
	data = ft_init(av[1]);
	mlx_loop_hook(data->mlx, ft_hooks, (void *)data);
	mlx_loop(data->mlx);
}
