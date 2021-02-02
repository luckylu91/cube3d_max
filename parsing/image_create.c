#include "parse.h"

int colored_image(void *mlx, int color, t_img *res)
{
	void *img;
	
	if (!(img = mlx_new_image(mlx, 1, 1)))
		return (-1);
	*res = img_from_ptr(img, 1, 1);
	color_pix(res, 0, 0, color);
	return (1);
}

int	load_sprite_image(void *mlx, int type, t_sprite_img *res)
{
	//TODO
	void *img;
	t_img im;
	int w;
	int h;

	if (type == PEA && !(img = mlx_xpm_file_to_image(mlx, "dot.xpm", &w, &h)))
		return (-1);
	if (type == GHOST && !(img = mlx_xpm_file_to_image(mlx, "red_face.xpm", &w, &h)))
		return (-1);
	im = img_from_ptr(img, w, h);
	res->im = im;
	if (type == PEA)
	{
		res->img_ratio.x = .2;
		res->img_ratio.y = .2;
		res->img_offset.x = 0.;
		res->img_offset.y = 0.;
	}
	else if (type == GHOST)
	{
		res->img_ratio.x = 1;
		res->img_ratio.y = 1;
		res->img_offset.x = 0.;
		res->img_offset.y = 0.;
	}
	return (1);
}