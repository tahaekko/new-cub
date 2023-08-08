/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 10:52:24 by msamhaou          #+#    #+#             */
/*   Updated: 2023/08/08 12:57:16 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


t_map_row	*ft_new_row(char *addr, t_collector **col)
{
	t_map_row	*node;

	node = c_malloc(sizeof(t_map_row), col);
	node->row = addr;
	node->next = NULL;
	node->back = NULL;
	return (node);
}

t_map_row	*ft_last_row(t_map_row *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_row_add_back(t_map_row **list, t_map_row *new_node)
{
	t_map_row	*last;

	if (!*list)
	{
		*list = new_node;
		return ;
	}
	last = ft_last_row(*list);
	last->next = new_node;
}
