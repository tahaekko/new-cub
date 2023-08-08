/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gsubstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 09:35:54 by msamhaou          #+#    #+#             */
/*   Updated: 2023/08/08 09:37:00 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_gsubstr(char const *s, unsigned int start, size_t len, t_collector **col)
{
	char	*str;

	if (!s)
		return (0);
	if (ft_strlen(s) < start)
	{
		str = c_malloc(1 * sizeof(char), col);
		*str = '\0';
		return (str);
	}
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	str = c_malloc((len + 1) * sizeof (char), col);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}
