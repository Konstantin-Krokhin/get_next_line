/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Konstantin Krokhin <kokrokhi@students.42wo +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:25:00 by Konstantin Krokh  #+#    #+#             */
/*   Updated: 2022/05/09 19:22:35 by Konstantin Krokh ###   ########.fr       */
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

size_t	gnl_strlen(const char *s)
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

char	*ft_strchr(const char *s, int c)
{
	char	*f;
	int		i;
	int		len;

	i = 0;
	f = (char *)s;
	len = gnl_strlen(f);
	if (c < 0 || c > 255)
		return (f);
	while (i <= len)
	{
		if (f[i] == c)
			return (&f[i]);
		i++;
	}
	return (NULL);
}

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	int				diff;
// 	unsigned char	*str1;
// 	unsigned char	*str2;

// 	diff = 0;
// 	if (n < 1)
// 		return (0);
// 	str1 = (unsigned char *)s1;
// 	str2 = (unsigned char *)s2;
// 	while (*str1 == *str2 && n > 1 && (*str1 != '\0' && *str2 != '\0'))
// 	{
// 		str1++;
// 		str2++;
// 		n--;
// 	}
// 	return (*str1 - *str2);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*str;
// 	size_t	s1_size;
// 	size_t	s2_size;

// 	s1_size = ft_strlen(s1);
// 	s2_size = ft_strlen(s2);
// 	if ((!s1 && !s2)
// 		|| (ft_strncmp(s1, s2, s1_size) == 0
// 			&& ft_strncmp("", s2, s2_size) == 0))
// 		return ("");
// 	str = malloc((s1_size + s2_size + 1) * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	ft_memmove(str, s1, s1_size);
// 	ft_memmove(str + s1_size, s2, s2_size);
// 	str[s1_size + s2_size] = '\0';
// 	return (str);
// }

char	*gnl_memmove(char *dest, char *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if (dest > src)
	{
		while (len-- > 0)
			dest[len] = src[len];
	}
	else
	{
		while (i < len)
		{
			dest[i] = src[i];
			i++;
		}
	}
	return (dest);
}

char	*gnl_calloc(int count)
{
	char	*stringy;
	int		i;

	i = 0;
	stringy = malloc (count * sizeof(char));
	if (!stringy)
		return (NULL);
	while (i < count)
		stringy[i++] = '\0';
	return (stringy);
}

char	*gnl_strjoin(char *str1, char *str2)
{
	int		len1;
	int		len2;
	char	*stringy;

	len2 = gnl_strlen(str2);
	len1 = gnl_strlen(str1);
	stringy = gnl_calloc((len1 + len2) + 1);
	if (!stringy)
		return (NULL);
	if (str1)
		gnl_memmove(stringy, str1, len1);
	gnl_memmove(stringy + len1, str2, len2);
	if (str1)
		free(str1);
	// if(str2)
	// 	free(str2);
	return (stringy);
}

char	*extract_line(char	*buf, int	*size)
{
	char	*line;
	int		i;

	i = 0;
	while (buf[i] != '\n')
		i++;
	line = (char *)malloc((i + 1) * sizeof(char));
	i = 0;
	while (buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	printf("EXTRACT LINE: %s", line);
	*size = i;
	return(line);
}

char	*get_next_line(int fd)
{
	static char	remainder[1024];
	char	buf[BUFFER_SIZE + 1];
	char	*line;
	char	*temp;
	int		size;
	int		i;

	line = NULL;
	if (fd < 0 || fd > 1023)
		return (NULL);
	if (remainder[0] != '\0')
	{
		if (ft_strchr(remainder, '\n')) // 1
		{
			printf("line2: %s", line);
			temp = extract_line(remainder, &size);
			line = gnl_strjoin(line, temp);
			free (temp);
			printf("line11: %s", line);
			ft_memmove(&remainder[0], &remainder[size], sizeof(remainder) - size);
			printf("rem: %s", remainder); 
		}
		else
		{
			line = gnl_strjoin(line, remainder);
			printf("END line: %s", line);
			remainder[0] = '\0';
			buf[i = read(fd, buf, BUFFER_SIZE)] = '\0';
			if (i == 0)
			{
				printf("HALLO: %s", line);
				return (line);
			}
			else
				{
					printf("buf: %s", buf);
					while (!ft_strchr(buf, '\n'))
					{
						printf("!line: %s", line);
						line = gnl_strjoin(line, buf);
						printf("!line: %s", line);
						buf[read(fd, buf, BUFFER_SIZE)] = '\0';		
					}
					if (ft_strchr(buf, '\n')) // 1
					{
						printf("line2: %s", line);
						temp = extract_line(buf, &size);
						line = gnl_strjoin(line, temp);
						free (temp);
						printf("line111: %s", line);
						ft_memmove(remainder, &buf[size], sizeof(remainder) - size);
						printf("rem: %s", remainder);
					}
				}
		}
	}
	else
	{
		buf[read(fd, buf, BUFFER_SIZE)] = '\0';
		printf("buf: %s", buf);
		while (!ft_strchr(buf, '\n') && buf[0] != '\0')
		{
			line = gnl_strjoin(line, buf);
			buf[read(fd, buf, BUFFER_SIZE)] = '\0';
		}
		if (ft_strchr(buf, '\n')) // 1
		{
			printf("line2: %s", line);
			temp = extract_line(buf, &size);
			line = gnl_strjoin(line, temp);
			free (temp);
			printf("line1111: %s", line);
			ft_memmove(remainder, &buf[size], sizeof(remainder) - size);
			printf("rem: %s", remainder);
		}
	}
	//remainder[0] = '\0';
	return (line);
}

// int	main(int argc, char *argv[])
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
// 		printf("<%s>", func_res);
// 	}
// 	//free(func_res);
// 	return(0);
// }

/*
char	*extract_line(char	*buf, int	*size)
{
	char	*line;
	int		i;
	
	i = 0;
	while (buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		line[i] = '\n';
	printf("line: %s", line);
	*size = i;
	return(line);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	static char	*line;
	int			size;
	char		*l;
	char		*remainder;
	
	if (buf[0] == '\0')
		buf[read(fd, buf, BUFFER_SIZE)] = '\0';
	if (buf[0] == '\0')
		return (NULL);
	if (ft_strchr(buf, '\n'))
	{
		l = extract_line(buf, &size);
		line = (char *)malloc((size + 1) * sizeof(char) + 1);
		ft_strjoin(line, l);
		ft_memmove(&buf[0], &buf[size + 1], sizeof(buf) - size);
		return(NULL);
	}
	else
	{
		//line[0] = '\0';
		
		remainder = ft_strjoin(remainder, buf);
		buf[0] = '\0';
		while (!ft_strchr(buf, '\n'))
		{
			if (buf[0] == '\0')
				buf[read(fd, buf, BUFFER_SIZE)] = '\0';
			l = extract_line(buf, &size);
			line = (char *)malloc((sizeof(remainder) + size + 1) * sizeof(char) + 1);
			ft_strjoin(line, remainder);
			ft_strjoin(line, l);
		}
	}
	return(line);
}
*/
// ----------
/*
char	*extract_line(char *buf, int *size, char *line, int *i)
{
	//if (buf[*size] == '\n') (*size)++;
	while (buf[*size] != '\n' && buf[*size] != '\0')
		(*size)++;
	//if (buf[*size-1] != '\0') (*size)--;
	printf("%d\n", *size);
	line = (char*)malloc((*size + 1) * sizeof(char) + 1); // size + 1 for the word with \n sign, and sizeof + 1 for the null terminator
	// printf("%s\n", buf);
	// printf("%d\n", *i);
	// printf("%s\n", line);
	while (*i <= *size)
	{
		line[*i] = buf[*i];
		(*i)++;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	static char	*line;
	int			i;
	static int	size;
	int	j;
	static int flag;
	char temp[sizeof(buf)];
	char *l;
	int o = 0;

	i = 0;
	if (buf[0] == '\0' || line[0] != '\0')
		buf[read(fd, buf, BUFFER_SIZE)] = '\0';
	if (buf[0] == '\0')
		return (NULL);
	if (flag != 1) line = extract_line(buf, &size, line, &i);
	//printf("%s\n", line);
	if (flag == 1)
	{
		while (o < sizeof(buf)) { temp[o] = buf[o]; o++; }
		buf[0] = '\0';
		buf[j = read(fd, buf, BUFFER_SIZE)] = '\0';
		printf("!!!! %d -- bufSIZE\n", j);
		printf("!!!!buf = %s -- buf\n", buf);
		line[0] = '\0';
		if (!ft_strchr(buf, '\n'))
		{
			ft_strjoin(line, temp);
			ft_strjoin(line, buf);
		}
		else
		{
			//size = 0;
			printf("!!!! %s" , ft_strjoin(line, temp));
			l = extract_line(buf, &size, line, &i);
			printf("!!!! %s" , ft_strjoin(line, l));
		}
		flag = 0;
	}
	else 
	{
		line[i] = '\0';
	}
	j = BUFFER_SIZE - size;
	if (j) 
	{
		ft_memmove(&buf[0], &buf[size + 1], j);
		if (!ft_strchr(buf, '\n') && j + size >= BUFFER_SIZE && j > 1) flag = 1;
		printf("buf = %s -- buf and SIZE %c\n", buf, buf[0]);
		size = 0;
	}
	if (j <= 1) size = 0;
	return (line);
}
*/