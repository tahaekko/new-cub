/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:31:41 by msamhaou          #+#    #+#             */
/*   Updated: 2023/06/26 19:10:23 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

int		ft_isnewline(char *s);
char	*ft_gstrjoin(char *s1, char *s2);
size_t	ft_linelen(char *str);
char	*get_next_line(int fd);
#endif
