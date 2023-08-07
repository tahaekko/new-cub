/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 13:43:54 by msamhaou          #+#    #+#             */
/*   Updated: 2023/08/07 15:28:27 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_print_err(int type)
{
	e_err	err;

	err = type;

	if (err == XPM)
		printf("XPM FAILED !\n");
	if (err == MLX)
		printf("MLX FAILED !\n");
	if (err == CUB)
		printf("MAP FILE FAILED !\n");
}

void	ft_free_error_type(t_collector **col, int type)
{
	ft_print_err(type);
	ft_free_addr(*col);
	exit(1);
}
