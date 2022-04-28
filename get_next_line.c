#include <fcntl.h> 
#include "stdio.h"
#include "unistd.h"
#include <stdlib.h>
#include "get_next_line.h"
#include "get_next_line_utils.c"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

char *ifRead(char *buf)
{
	return (buf = (char *)malloc(BUFFER_SIZE * sizeof(char) + 1));
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;
	int			i;
	int			size;

	i = 0;
	size = 0;
	buf = ifRead(buf);
	if (!*buf)
		read(fd, buf, BUFFER_SIZE + 1);
	buf[sizeof(buf) + 1] = '\0';
	while (buf[size] != '\n' && buf[size] != '\0')
		size++;
	line = (char *)malloc(size * sizeof(char) + 1);
	while (i < size)
	{
		line[i] = buf[i];
		i++;
	}
	line[i] = '\0';

	return (line);
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	*func_res;

	fd = open(argv[1], O_RDONLY);
	func_res = "";
	while (func_res != NULL)
	{
		func_res = get_next_line(fd);
		write(1, func_res, sizeof(func_res));
	}
	free(func_res);
	return(0);
}
