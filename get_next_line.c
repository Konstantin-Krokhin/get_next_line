/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Konstantin Krokhin <kokrokhi@students.42wo +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:25:00 by Konstantin Krokh  #+#    #+#             */
/*   Updated: 2022/04/29 20:58:29 by Konstantin Krokh ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h> 
#include "stdio.h"
#include <stdlib.h>
#include "get_next_line.h"
#include "get_next_line_utils.c"
#include <stdbool.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

size_t	ft_strlen(const char *s)
{
	int	size;

	size = 0;
	if (!s)
		return (0);
	while (s[size] != '\0')
		size++;
	return (size);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;

	d = (char *)dst;
	s = (char *)src;
	if (dst == src)
		return (dst);
	if (s < d)
	{
		while (len--)
			*(d + len) = *(s + len);
		return (dst);
	}
	while (len-- != 0)
		*d++ = *s++;
	return (dst);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			i;
	int	size;
	static int	j;

	i = 0;
	size = 0;
	if (buf[0] == '\0')
		buf[j = read(fd, buf, BUFFER_SIZE)] = '\0';
	if (buf[0] == '\0')
		return (NULL);
	while (buf[size] != '\n' && buf[size] != '\0')
		size++;
	printf("%d\n", size);
	line = (char *)malloc((size + 1) * sizeof(char) + 1);
	while (i <= size)
	{
		line[i] = buf[i];
		i++; 
	}
	line[i] = '\0';
	//j += size;
	if (BUFFER_SIZE - size) ft_memmove(&buf[0], &buf[size + 1], BUFFER_SIZE - size);
	return (line);
}


// int	main(char *argv[])
// {
// 	int		fd;
// 	char	*func_res;
// 	int		i;

// 	fd = open(argv[1], O_RDONLY);
// 	func_res = "";
// 	i = 0;
// 	while (func_res != NULL)
// 	{
// 		func_res = get_next_line(fd);
// 		printf("%s", func_res);
// 	}
// 	free(func_res);
// 	return(0);
// }