#include "mlx.h"
#include <stdio.h>

int main()
{
	void *mlx = mlx_init();
	if (mlx)
		printf("Success\n");
	else
		printf("Fail\n");
	return (0);
}
