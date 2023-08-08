/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:43:54 by msamhaou          #+#    #+#             */
/*   Updated: 2023/08/08 09:26:20 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_print_err(int type)
{
	e_err	err;

	err = type;

	if (err == XPM)
		ft_putendl_fd("XPM FAILED !", 2);
	if (err == MLX)
		ft_putendl_fd("MLX FAILED !", 2);
	if (err == CUB)
		ft_putendl_fd("MAP FILE FAILED !", 2);
	if (err == VALID)
		ft_putendl_fd("INVALID MAP FILE !", 2);
	if (err == COLOR_SET)
		ft_putendl_fd("INVALID COLOR SET !", 2);
}

void	ft_free_error_type(t_collector **col, int type)
{
	ft_print_err(type);
	ft_free_addr(*col);
	exit(1);
}
