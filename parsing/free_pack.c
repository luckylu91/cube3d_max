#include "cub3d.h"

static void	free_img(void *mlx, t_img *im)
{
	if (im->img)
		mlx_destroy_image(mlx, im->img);
	ft_bzero(im, sizeof(t_img));
}

void		free_sprite(void *sprite_ptr)
{
	t_sprite *sprite;

	sprite = (t_sprite*)sprite_ptr;
	ft_lstclear(&sprite->path, &free);
	free(sprite);
}

int			free_pack(t_pack *p)
{
	int i;

	free_img(p->mlx, &p->win_img[0]);
	free_img(p->mlx, &p->win_img[1]);
	i = -1;
	while (++i < 6)
	{
		free_img(p->mlx, &p->cube_faces[i]);
		free(p->cube_faces_fnames[i]);
	}
	ft_lstclear(&p->sprites, &free_sprite);
	i = -1;
	while (++i < ft_strlen(SPRITES))
		mlx_destroy_image(p->mlx ,p->sprite_images[i].im.img);
	free(p->sprite_images);
	i = -1;
	while (++i < p->width)
		free(p->dist_array[i]);
		return (-1);
	mlx_destroy_window(p->mlx, p->win);
	return (-1);
}

int		free_pack_and_quit(t_pack *p)
{
	free_pack(p);
	exit(0);
	return (0);
}