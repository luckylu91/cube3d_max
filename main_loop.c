#include "cub3d.h"
#include "parsing/parse.h"

void mloop()
{
	void *mlx;
	t_pack p;
	
	if (!(mlx = mlx_init()))
	{
		ft_printf("Error\nWhile loading mlx\n");
		exit(-1);
	}
	if (init(&p, mlx, "scene.cub") == -1)
		exit(-1);
	p.mini_origin.x = 100;
	p.mini_origin.y = 100;
	p.mini_width = 200;
	p.nanosec = clock_gettime_nsec_np(CLOCK_REALTIME);
	p.time_total = 0.;
	p.time_loop = 0.;

	int x, y;
	for (y = 0; y < p.map.height; y++)
	{
		for (x = 0; x < p.map.width; x++)
		{
			printf("%c", p.map.grid[x][y]);
		}
		printf("\n");
	}

	mlx_mouse_hide();
	mlx_hook(p.win, 2, 1L << 0, &key_press_hook, &p);
	mlx_hook(p.win, 3, 1L << 1, &key_release_hook, &p);
	mlx_hook(p.win, 6, 1L << 6, &motion_hook, &p);
	mlx_hook(p.win, 17, 0, &free_pack_and_quit, &p);
	mlx_loop_hook(mlx, &loop_hook, &p);
	mlx_loop(mlx);
}