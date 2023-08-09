/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:44:37 by msamhaou          #+#    #+#             */
/*   Updated: 2023/08/09 15:27:34 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*ft_img_alloc()
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	return (img);
}

void	ft_set_img(t_img *img, int width, int height,t_data *data)
{
	img->img_ptr = mlx_new_image(data->mlx, width, height);
	// img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line, &img->endian);
}
