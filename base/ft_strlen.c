#include "parsing.h"

int	ft_strlen_c(char *str, char c)
{
	int	len;

	len = 0;
	while (*str != '\0' && *str != c)
	{
		++len;
		++str;
	}
	return (len);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}


