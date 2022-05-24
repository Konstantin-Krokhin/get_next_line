/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Konstantin Krokhin <kokrokhi@students.42wo +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:25:00 by Konstantin Krokh  #+#    #+#             */
/*   Updated: 2022/05/24 21:32:32 by Konstantin Krokh ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	join_line_with_buf_till_newline(char **line, char *buf)
{
	size_t	cnt;
	size_t	i;
	char	*rtn_line;

	if (!*line || !buf)
		return ;
	i = 0;
	cnt = gnl_strlen(line[0]) + gnl_strlen(buf) + 1;
	rtn_line = gnl_calloc(cnt * sizeof(char));
	while (line[0][i])
	{
		rtn_line[i] = line[0][i];
		i++;
	}
	free(line[0]);
	cnt = i;
	i = 0;
	while (buf[i] != '\n' && buf[i] != '\0')
		rtn_line[cnt++] = buf[i++];
	if (buf[i] == '\n')
		rtn_line[cnt] = '\n';
	line[0] = rtn_line;
}

char	*return_free_line(char *line)
{
	free(line);
	return (NULL);
}

char	*return_last_line(char **line, char *buf)
{
	join_line_with_buf_till_newline(line, buf);
	buf[0] = '\0';
	return (*line);
}

void	move_buf_to_next_line(char *buf)
{
	size_t	buf_new_line_position;
	size_t	left_buf;

	buf_new_line_position = gnl_strlen(buf)
		- gnl_strlen(ft_strchr(buf, '\n') + 1);
	left_buf = gnl_strlen(buf) - buf_new_line_position;
	ft_memmove(buf, &buf[buf_new_line_position], left_buf);
	ft_memset(&buf[left_buf], '\0', buf_new_line_position);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			state;

	if (fd < 0)
		return (NULL);
	line = gnl_calloc(sizeof(char));
	while (!ft_strchr(buf, '\n'))
	{
		if (*buf)
			join_line_with_buf_till_newline(&line, buf);
		state = read(fd, buf, BUFFER_SIZE);
		if (state <= 0 && !(*line))
			return (return_free_line(line));
		buf[state] = '\0';
		if (!ft_strchr(buf, '\n') && state < BUFFER_SIZE)
			return (return_last_line(&line, buf));
	}
	join_line_with_buf_till_newline(&line, buf);
	move_buf_to_next_line(buf);
	return (line);
}

// int main()
// {
// 	int		fd;
// 	char	*func_res;
// 	fd = open("f.txt", O_RDONLY);
// 	while (func_res != NULL)
// 	{
// 		func_res = get_next_line(fd);
// 		printf("<%s>", func_res);
// 	}
// 	free(func_res);
// 	return(0);
// 	return (0);
// }