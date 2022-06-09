#include "parsing.h"
#include <stdlib.h>

void	*ft_realloc(void *ptr, int ptr_size, int new_size)
{
	char	*temp;
	char	*cp_ptr;
	int		i;

	temp = (char *)malloc(new_size);
	if (temp == NULL)
		print_error(NULL);
	cp_ptr = (char *)ptr;
	i = -1;
	while (++i < ptr_size)
		temp[i] = cp_ptr[i];
	free(ptr);
	return (temp);
}
