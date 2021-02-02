#include "cub3d.h"

int *get_pix_address(t_img *im, int x, int y)
{
	return ((int*)(im->data + x * im->bpp / 8 + y * im->lsize));
}

void *copyimg(t_img *dest, t_img *src, t_pt2d start, t_pt2d stop)
{
	int x, y;

	for (x = start.x; x <= stop.x; x++)
	{
		for (y = start.y; y <= stop.y; y++)
		{
			*get_pix_address(dest, x - start.x, y - start.y) = *get_pix_address(src, x, y);
		}
	}
}

int main()
{
	void *mlx = mlx_init();
	int width, height;
	void *img = mlx_xpm_file_to_image(mlx, "cartoon_65textures.xpm", &width, &height);
	printf("%d x %d\n", width, height);
	t_img im = img_from_ptr(img, width, height);
	t_pt2d WALL_START = {767, 767};
	t_pt2d WALL_STOP = {866, 866};
	t_pt2d FLOOR_START = {893, 513};
	t_pt2d FLOOR_STOP = {992, 612};
	t_pt2d CEIL_START = {7, 7};
	t_pt2d CEIL_STOP = {106, 106};
	void *img_wall = mlx_new_image(mlx, 100, 100);
	void *img_floor = mlx_new_image(mlx, 100, 100);
	void *img_ceil = mlx_new_image(mlx, 100, 100);
	t_img im_wall = img_from_ptr(img_wall, 100, 100);
	t_img im_floor = img_from_ptr(img_floor, 100, 100);
	t_img im_ceil = img_from_ptr(img_ceil, 100, 100);
	copyimg(&im_wall, &im, WALL_START, WALL_STOP);
	copyimg(&im_floor, &im, FLOOR_START, FLOOR_STOP);
	copyimg(&im_ceil, &im, CEIL_START, CEIL_STOP);

	
	mlx_loop(mlx);
}