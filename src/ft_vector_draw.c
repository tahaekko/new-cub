/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tahaexo <tahaexo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:24:33 by msamhaou          #+#    #+#             */
/*   Updated: 2023/09/30 02:46:38 by tahaexo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



double	*ft_hypo_calc(double *a, double *b)
{
	double	*hypo;
	double	x;
	double	y;
	// double	deg;

	x = fabs(b[0] - a[0]);
	y = fabs(a[1] - b[1]);

	hypo = malloc(sizeof(double) * 2);
	hypo[0] = sqrt((x * x) + (y * y));
	hypo[1] = asin(y / hypo[0]);

	return (hypo);
}
void	ft_vect_draw(double *a, double *b, int color, t_data *data, t_img *img)
{
	double	i;
	double	*hypo;
	double	*hypo_max;
	double	x;
	double	y;

	i = 0;
	printf("%d\n", (int)b[0]);
	hypo = ft_hypo_calc(a, b);

	x = 0;
	y = 0;
	while (i < hypo[0])
	{
		if ((int)a[0] + x > 0 && (int)a[0] + x < WIDTH &&  (int)a[1] + y > 0 && (int)a[1] + y < HEIGHT)
			ft_put_pix(img,(int)a[0] + x, (int)a[1] + y, color, data);
		x+= cos(hypo[1]);
		y += sin(hypo[1]);
		printf ("%f\n",y);
		i++;
	}
}



void	ft_swap_vect(t_vertex **a, t_vertex **b)
{
	t_vertex	**tmp;

	tmp = a;
	*a = *b;
	*b = *tmp;
}
