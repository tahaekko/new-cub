#include <cub3d.h>

void	print_float(float f)
{
	printf("%f\n",f);
}

void	print_int(int d)
{
	printf("%d\n",d);
}

void	ft_draw_debug(t_data *data, int type)
{
	for (int i = 0; i < WIDTH; i++)
	{
		if (data->ray[i].is_vertical)
			ft_draw_ray_vertical(data, data->player, data->ray[i]);
		else
			ft_draw_ray_horizontal(data, data->player, data->ray[i]);
	}
}
