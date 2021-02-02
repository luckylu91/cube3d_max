#include "parse.h"

static int open_file_error(char *fname)
{
	int fd;

	if ((fd = open("scene.cub", O_RDONLY)) == -1)
	{
		ft_printf("Error\nWhile opening %s\n", fname);
		perror(NULL);
		exit(-1);
	}
	return (fd);
}

static void close_file_error(int fd, char *fname, t_list **scene_lines)
{
	if (close(fd) == -1)
	{
		ft_printf("Error\nWhile closing %s\n", fname);
		perror(NULL);
		ft_lstclear(scene_lines, &free);
		exit(-1);
	}
	else if (!*scene_lines)
	{
		ft_printf("Error\nWhile reading %s\n", fname);
		perror(NULL);
		exit(-1);
	}
}

int init(t_pack *p, void *mlx, char *scene_path)
{
	int		scene_fd;
	t_list	*scene_lines;
	int		i;

	ft_bzero(p, sizeof(t_pack));
	p->mlx = mlx;
	if (!(p->sprite_images = ft_calloc(ft_strlen(SPRITES), sizeof(t_sprite_img))))
		return (free_pack(p));
	i = -1;
	while (++i < ft_strlen(SPRITES))
	{
		if (load_sprite_image(p->mlx, SPRITES[i], &p->sprite_images[i]) == -1)
			return (free_pack(p));
	}
	scene_fd = open_file_error(scene_path);
	scene_lines = file_to_list(scene_fd);
	close_file_error(scene_fd, scene_path, &scene_lines);
	if (parse_all(scene_lines, p) == -1)
		return (free_pack(p));
	ft_lstclear(&scene_lines, &free);
	return (1);
}

int set_win_elements(t_pack *p)
{
	void *img1;
	void *img2;
	int mini_dimentions[2];

	img1 = mlx_new_image(p->mlx, p->width, p->height);
	img2 = mlx_new_image(p->mlx, p->width, p->height);
	p->win = mlx_new_window(p->mlx, p->width, p->height, "Cub3D");
	p->win_img[0] = img_from_ptr(img1, p->width, p->height);
	p->win_img[1] = img_from_ptr(img2, p->width, p->height);
	if (!p->win || !img1 || !img2)
		return (win_image_error(p));
	p->win_buffered = 0;
	p->key_pressed = 0;
	return (1);
}

static int load_image(t_pack *p, int cardinal, t_img *res)
{
	void	*img;
	int		w;
	int		h;
	int color;

	if (p->floor_ceil_are_sprites
		|| cardinal == NORTH
		|| cardinal == SOUTH
		|| cardinal == EAST
		|| cardinal == WEST)
	{
		if (!(img = mlx_xpm_file_to_image(
				p->mlx,
				p->cube_faces_fnames[cardinal],
				&w, &h)))
			return (-1);
		*res = img_from_ptr(img, w, h);
	}
	else
	{
		color = (cardinal == FLOOR ? p->floor_color : p->ceil_color);
		if (colored_image(p->mlx, color, res) == -1)
			return (-1);
	}
	return (0);
}


int set_cube_faces_sprites(t_pack *p)
{
	int i;

	i = -1;
	while (++i < 6)
	{
		if (load_image(p, i, &p->cube_faces[i]) == -1)
			return (load_cubeface_error(p, i));
	}
	return (1);
}