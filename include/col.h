/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   col.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:45:25 by msamhaou          #+#    #+#             */
/*   Updated: 2023/08/09 19:02:25 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COL_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

typedef struct s_collector
{
	void				*addr;
	struct s_collector	*next;
}	t_collector;

void	*c_malloc(size_t size, t_collector **list);
t_collector	*ft_new_collector(void	*addr, t_collector **list);
void	ft_free_collector(t_collector **node);
void	ft_free_addr(t_collector *list);


#endif
