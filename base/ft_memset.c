#include "../minirt.h"

void	ft_memset(void *target, unsigned int size, int input)
{
	char				*cp_target;
	unsigned int		i;
	unsigned char		input_c;

	cp_target = (char *)target;
	i = -1;
	input_c = (unsigned char)input;
	while (++i < size)
		cp_target[i] = input_c;
}
