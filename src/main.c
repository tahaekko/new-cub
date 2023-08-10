/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 10:09:02 by msamhaou          #+#    #+#             */
/*   Updated: 2023/08/09 19:02:34 by msamhaou         ###   ########.fr       */
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
	ft_free_addr(data->col);
	printf("point3 %p\n", data->col);
	ft_free_collector(&data->col);
	// mlx_terminate(data->mlx);
	exit(0);
}

int	ft_exit(t_data * data)
{
	ft_free_all(data);
	return(1);
}

 void	ft_hooks(mlx_key_data_t keydata, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		ft_free_all(data);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_texture *text;

	// atexit(foo);
	if (!av[1])
		exit(1);
	data = ft_init(av[1]);
	printf("HEAD1 %p\n", data->col);
	mlx_key_hook(data->mlx, ft_hooks, (void *)data);
	mlx_loop(data->mlx);
}
