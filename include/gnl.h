/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 11:14:40 by msamhaou          #+#    #+#             */
/*   Updated: 2023/08/07 10:29:19 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"
# include "col.h"
# define BUFFER_SIZE 5

size_t	ft_linelen(char *str);
int		ft_isnewline(char *s);
char	*ft_gstrjoin(char *s1, char *s2, t_collector **col);
char	*gnl(int fd, t_collector **col);

#endif
