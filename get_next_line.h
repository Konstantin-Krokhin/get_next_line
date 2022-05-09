/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Konstantin Krokhin <kokrokhi@students.42wo +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:25:21 by Konstantin Krokh  #+#    #+#             */
/*   Updated: 2022/05/09 21:15:22 by Konstantin Krokh ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h> 
# include "stdio.h"
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
size_t	gnl_strlen(const char *s);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strchr(const char *s, int c);
char	*gnl_calloc(int count);
char	*gnl_strjoin(char *str1, char *str2);

#endif