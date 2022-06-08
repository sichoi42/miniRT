#include "parsing.h"
#include <unistd.h>

void	print_error(char *message)
{
	write(2, "Error\n", 6);
	if (message == NULL)
		perror(NULL);
	else
		write(2, message, ft_strlen(message));
	exit(1);
}
