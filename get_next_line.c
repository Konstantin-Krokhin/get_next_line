/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Konstantin Krokhin <kokrokhi@students.42wo +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:25:00 by Konstantin Krokh  #+#    #+#             */
/*   Updated: 2022/05/23 15:20:18 by Konstantin Krokh ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	*size = i;
	return (line);
}

char	*return_line_add_remainder(char *remainder, int *s, char **line, int fd)
{
	int size;
	int i;
	char *temp;
	char buf[BUFFER_SIZE + 1];

	size = 0;
	*line = gnl_strjoin(*line, remainder);
	remainder = NULL;
	buf[i = read(fd, buf, BUFFER_SIZE)] = '\0';
	if (i > 0)
	{
		if (!ft_strchr(buf, '\n'))
		{
			*line = gnl_strjoin(*line, buf);
			buf[read(fd, buf, BUFFER_SIZE)] = '\0';
		}
		if (ft_strchr(buf, '\n'))
		{
			temp = extract_line(buf, &size);
			*line = gnl_strjoin(*line, temp);
			free (temp);
			ft_memmove(&remainder[0], &buf[size], sizeof(remainder) - size);
		}
	}
	*s = size;
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	remainder[1024];
	char		buf[BUFFER_SIZE + 1];
	char		*line;
	char		*temp;
	int			size;
	int	i;

	line = NULL;
	if (fd < 0 || fd > 1024 || read (fd, NULL, 0) || BUFFER_SIZE <= 0)
		return (NULL);
	if (remainder[0] != '\0')
	{
		if (ft_strchr(remainder, '\n')) // 1
		{
			//line = extract_line_and_move_buf(&remainder[0], line, &size); LEAK 0x7ffe3f405850
			temp = extract_line(remainder, &size);
			line = gnl_strjoin(line, temp);
			free (temp);
			ft_memmove(&remainder[0], &remainder[size], sizeof(remainder) - size);
		}
		else
		{
			//-----------------------------------
			line = gnl_strjoin(line, remainder);
			remainder[0] = '\0';
			buf[i = read(fd, buf, BUFFER_SIZE)] = '\0';
			if (i == 0)
				return (line);
			else
			{
				if (!ft_strchr(buf, '\n'))
				{
					line = gnl_strjoin(line, buf);
					buf[read(fd, buf, BUFFER_SIZE)] = '\0';
				}
				if (ft_strchr(buf, '\n'))
				{
					temp = extract_line(buf, &size);
					line = gnl_strjoin(line, temp);
					free (temp);
					ft_memmove(&remainder, &buf[size], sizeof(remainder) - size);
				}
			}
		}
	}
	else
	{
		buf[i = read(fd, buf, BUFFER_SIZE)] = '\0';
		while (!ft_strchr(buf, '\n') && buf[0] != '\0')
		{
			line = gnl_strjoin(line, buf);
			buf[i = read(fd, buf, BUFFER_SIZE)] = '\0';
		}

		if (ft_strchr(buf, '\n')) // 1
		{
			temp = extract_line(buf, &size);
			line = gnl_strjoin(line, temp);
			free (temp);
			if ((int)sizeof(remainder) > size)
				ft_memmove(remainder, &buf[size], sizeof(remainder) - size);
		}
	}
	return (line);
}

// char	*extract_line_and_move_buf(char *remainder, char *line, int *size)
// {
// 	char		*temp;
	
// 	temp = extract_line(remainder, size);
// 	line = gnl_strjoin(line, temp);
// 	free (temp);
// 	ft_memmove(&remainder[0], &remainder[*size], sizeof(remainder) - *size);
	
// 	return (line); // buf ??
// }

// char	*extract_line_and_move_buf_2(char *remainder, char *buf, char *line, int *size)
// {
// 	char	*temp;
	
// 	if (ft_strchr(buf, '\n'))
// 	{
// 		temp = extract_line(buf, size);
// 		line = gnl_strjoin(line, temp);
// 		free (temp);
// 		if ((int)sizeof(remainder) > *size)
// 			ft_memmove(remainder, &buf[*size], sizeof(remainder) - *size);
// 	}
// 	return (line);
// }

// -------------------------------------------- OTHER SOLUTIONS --------------------------------------------------------------------
// int	main(int argc, char *argv[])
// {
// 	int		fd;
// 	char	*func_res;
// 	int		i;

// 	fd = open("f.txt", O_RDONLY);
// 	func_res = "";
// 	i = 0;
// 	while (func_res != NULL)
// 	{
// 		func_res = get_next_line(fd);
// 		printf("<%s>", func_res);
// 	}
// 	free(func_res);
// 	return(0);
// }

// -----------

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