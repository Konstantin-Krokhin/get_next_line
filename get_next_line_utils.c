/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Konstantin Krokhin <kokrokhi@students.42wo +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:25:17 by Konstantin Krokh  #+#    #+#             */
/*   Updated: 2022/05/09 21:13:57 by Konstantin Krokh ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifndef GET_NEXT_LINE_UTILS
# define GET_NEXT_LINE_UTILS

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
		ft_memmove(stringy, str1, len1);
	ft_memmove(stringy + len1, str2, len2);
	if (str1)
		free(str1);
	return (stringy);
}

#endif