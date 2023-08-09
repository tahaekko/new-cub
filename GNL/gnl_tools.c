/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:17:04 by msamhaou          #+#    #+#             */
/*   Updated: 2023/08/09 17:29:28 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

size_t	ft_linelen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

int	ft_isnewline(char *s)
{
	char	*ps;

	if (!s)
		return (0);
	ps = s;
	while (*ps)
	{
		if (*ps == '\n')
			return (1);
		ps++;
	}
	return (0);
}

char	*ft_gstrjoin(char *s1, char *s2, t_collector **col)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = (char *)c_malloc(1 * sizeof(char), col);
		s1[0] = '\0';
	}
	str = c_malloc((sizeof(char)*(ft_strlen(s1) + ft_strlen(s2) + 1)), col);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
