/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gatoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 09:42:33 by msamhaou          #+#    #+#             */
/*   Updated: 2023/08/08 09:48:43 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_gatoi(const char *str, t_collector **col)
{
	size_t	res;

	res = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	if (!(*str >= '0' && *str <= '9'))
		ft_free_error_type(col, 4);
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += *str - '0';
		if (res > 255)
			ft_free_error_type(col, 4);
		str++;
	}
	return (res);
}
