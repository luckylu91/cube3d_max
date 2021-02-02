#include "ft_printf.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Error. Usage : ./a.out [p|m]\n");
		return (-1);
	}
	if (strcmp(argv[1], "p") == 0)
		printf("%x", -1);
	else if (strcmp(argv[1], "m") == 0)
		ft_printf("%x", -1);
	else
		fprintf(stderr, "Error. Usage : ./a.out [p|m]\n");
	return (0);
}
