#include <unistd.h>

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

char	*ft_strchr(const char *s, int c)
{
	char	*f;
	int		i;
	int		len;

	i = 0;
	f = (char *)s;
	len = ft_strlen(f);
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
