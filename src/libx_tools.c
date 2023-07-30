/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libx_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:25:15 by msamhaou          #+#    #+#             */
/*   Updated: 2023/07/24 11:33:17 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_pix(t_img *img, int x, int y, int color,t_data *data)
{
	char	*addr;

	addr = img->addr + ((y * img->line) + (x * img->bpp/8));
	*(int *)addr = color;
}

void	ft_put_main_img(t_data *data)
{
	mlx_put_image_to_window(data->mlx,data->win,data->main_img->img_ptr, 0,0);
}
int	color_code(int r ,int g ,int b)
{
	return (r << 16 | g << 8 | b);
}
