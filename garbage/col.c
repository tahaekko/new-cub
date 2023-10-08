/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tahaexo <tahaexo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:44:43 by msamhaou          #+#    #+#             */
/*   Updated: 2023/10/08 19:37:59 by tahaexo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "col.h"

void	ft_free_all_malloc_err(t_collector **col)
{
	ft_free_addr(*col);
	ft_free_collector(*col);
	ft_putendl_fd("MALLOC FAILED !", 2);
	exit(1);
}

void	ft_free_collector(t_collector *node)
{
	t_collector	*tmp;

	tmp = NULL;
	printf("%p\n", node);
	while (node)
	{
		tmp = (node);
		node = (node)->next;
		printf("node freed %p\n", tmp);
		free(tmp);
		tmp = NULL;
	}
}

void	ft_free_addr(t_collector *list)
{
	t_collector	*head;
	void	*tf;

	head = list;
	while (head != NULL)
	{
		tf = head->addr;
		free(tf);
		tf = NULL;

		head = (head)->next;
	}
	// list = head;
}

t_collector	*ft_lastlst_collector(t_collector *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_collector_add_back(t_collector **list, t_collector *new_node)
{
	t_collector	*last;

	if (!new_node)
	{
		ft_free_all_malloc_err(list);
	}
	if (!(*list))
	{
		("here\n");
		*list = new_node;
		return ;
	}
	last = ft_lastlst_collector(*list);
	last->next = new_node;
}

void	*c_malloc(size_t size, t_collector **list)
{
	void	*ret;
	t_collector *new_col;

	new_col = NULL;
	ret = malloc(size);
	if (!ret)
		ft_free_all_malloc_err(list);
	new_col = ft_new_collector(ret, list);
	ft_collector_add_back(list, new_col);
	return (ret);
}

t_collector	*ft_new_collector(void	*addr, t_collector **list)
{
	t_collector	*node;

	node = malloc(sizeof(t_collector));
	("node alloc %p\n", node);
	if (!node)
		ft_free_all_malloc_err(list);
	node->addr = addr;
	node->next = NULL;
	return (node);
}
