#include "../minirt.h"
#include <unistd.h>

int	ft_read(int fd, char *buf, int size)
{
	int read_size;

	read_size = read(fd, buf, size);
	if (read_size == -1)
		print_error(NULL);
	return (read_size);
}
