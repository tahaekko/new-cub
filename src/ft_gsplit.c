/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gsplit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:08:45 by msamhaou          #+#    #+#             */
/*   Updated: 2023/08/08 09:37:41 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t	word_count(const char	*s, char c)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			counter++;
		while (s[i] != c && s[i])
			i++;
	}
	return (counter);
}

static void	ft_sne(const char *s, size_t *start, size_t *end, char c)
{
	*start = *end;
	while (s[*start] == c && s[*start])
		*start += 1;
	*end = *start;
	while (s[*end] != c && s[*end])
		*end += 1;
}

char	**ft_gsplit(char const *s, char c, t_collector **col)
{
	char	**split;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s)
		return (0);
	split = (char **)c_malloc((word_count(s, c) + 1) * sizeof (char *), col);
	if (!split)
		return (0);
	i = 0;
	end = 0;
	while (i < word_count(s, c))
	{
		ft_sne(s, &start, &end, c);
		split[i] = ft_gsubstr(s, start, end - start, col);
		if (!split[i])
		{
			return (NULL);
		}
		i++;
	}
	split[i] = NULL;
	return (split);
}
