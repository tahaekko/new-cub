/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:24:33 by msamhaou          #+#    #+#             */
/*   Updated: 2023/07/24 13:36:51 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_hypo_calc(t_vertex *a, t_vertex *b)
{
	double	hypo;
	double	x;
	double	y;

	x = (b->x - a->x);
	y = (a->y - b->y);
	hypo = ((x * x) + (y * y));
	return (hypo);
}

void	ft_swap_vect(t_vertex **a, t_vertex **b)
{
	t_vertex	**tmp;

	tmp = a;
	*a = *b;
	*b = *tmp;
}
