#include "parse.h"

int load_sprite_error(t_pack *p)
{
	int i;
	ft_printf("Error\n");
	ft_printf("Error while loading sprites images\n");
	i = -1;
	while (++i < ft_strlen(SPRITES))
	{
		mlx_destroy_image(p->mlx, p->sprite_images[i].im.img);
		p->sprite_images[i].im.img = NULL;
	}
	// equivalent of lstclear
	return (-1);
}

int win_image_error(t_pack *p)
{
	ft_printf("Error\n");
	ft_printf("Error while creating window-related images\n");
	if (p->win_img[0].img)
		mlx_destroy_image(p->mlx, p->win_img[0].img);
	if (p->win_img[1].img)
		mlx_destroy_image(p->mlx, p->win_img[1].img);
	return (-1);
}

int load_cubeface_error(t_pack *p, int i)
{
	ft_printf("Error\n");
	ft_printf("Error while loading cube-face-sprite num. %d\n", i);
	while (--i >= 0)
		mlx_destroy_image(p->mlx, p->cube_faces[i].img);
	return (-1);
}