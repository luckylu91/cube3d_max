#include "mlx.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct	s_param
{
	void		*mlx_ptr;
	void		*win_ptr;
}				t_param;

typedef enum	e_colors
{
	WHITE = 0X00FFFFFF
}				t_colors;

int		ilen(int n)
{
	int size;

	if (n == 0)
		return (1);
	if (n < 0)
		return (0);
	size = 0;
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*itoa(int n)
{
	int		size;
	int		i;
	char	*res;

	size = ilen(n);
	if (!(res = malloc(size + 1)))
		return (NULL);
	res[size] = '\0';
	while (size)
	{
		res[size - 1] = n % 10;
		n /= 10;
		size--;
	}
	return (res);
}

int key_hook(int keycode, void *paramaddr)
{
	t_param	*param = (t_param*)paramaddr;
	printf("keycode = %d\n", keycode);
	return (1);
}

int mouse_hook(int button, int x, int y, void *paramaddr)
{
	t_param	*param = (t_param*)paramaddr;
	printf("mouse button = %d\n", button);
	printf("mouse      x = %d\n", x);
	printf("mouse      y = %d\n", y);
	return (1);
}

int main()
{
	t_param param;

	void *mlx_ptr = mlx_init();
	void *win_ptr = mlx_new_window(mlx_ptr, 200, 160, "Who reads this ?");
	param.win_ptr = win_ptr;
	param.mlx_ptr = mlx_ptr;
	mlx_key_hook(win_ptr, &key_hook, &param);
	mlx_mouse_hook(win_ptr, &mouse_hook, &param);
	mlx_loop(mlx_ptr);
}