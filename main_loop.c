#include "cub3d.h"
#include "parse.h"

static int	handle_parameters(int argc, char **argv)
{
	int scene_fd;

	if ((argc != 2 && argc != 3) || (argc == 3 && ft_strcmp(argv[2], "--save")))
	{
		message_error("Usage : ./pacu path_to_scene.cub [--save]");
		exit(-1);
	}
	if ((scene_fd = open(argv[1], O_RDONLY)) < 0)
	{
		perror(NULL);
		exit(-1);
	}
	return (scene_fd);
}

void	mloop(int argc, char **argv)
{
	void	*mlx;
	t_pack	p;
	int		scene_fd;

	//
	setbuf(stdout, NULL);
	//
	scene_fd = handle_parameters(argc, argv);
	srand((unsigned int)time(NULL));
	if (!(mlx = mlx_init()))
	{
		message_error("While loading mlx");
		exit(-1);
	}
	if (pack_init(&p, mlx, scene_fd) == -1)
		exit(-1);
	if (argc == 3)
		generate_bmp("result.bmp", &p);
	mlx_expose_hook(p.win, &expose_hook, &p);
	mlx_hook(p.win, 17, 0, &free_pack_and_quit, &p);
	//// linux
	start_game(&p);
	//// end linux
	// if (p.game_on)
	// 	start_menu(&p);
	// else
	// 	start_game(&p);
	mlx_loop(p.mlx);
}
