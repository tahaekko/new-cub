/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tahaexo <tahaexo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 13:44:37 by msamhaou          #+#    #+#             */
/*   Updated: 2023/09/26 03:27:22 by tahaexo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*ft_img_alloc(t_data *data)
{
	t_img	*img;

	img = c_malloc(sizeof(t_img), &data->col);
	return (img);
}

/* /!\ need protect */
void	ft_set_img(t_img *img, int width, int height,t_data *data)
{
	img->img_ptr = mlx_new_image(data->mlx, width, height);
	printf("here\n");
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line, &img->endian);
}
