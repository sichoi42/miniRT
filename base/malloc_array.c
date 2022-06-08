#include "parsing.h"
#include <stdlib.h>

void	*malloc_array(int size, int len)
{
	void	*temp;

	temp = malloc(size * len);
	if (temp == NULL)
		print_error(NULL);
	return (temp);
}
