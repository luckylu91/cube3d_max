#include "cub3d.h"
#include "parse.h"

void print_ipt2d(void *content)
{
	t_ipt2d *apt = content;
	printf("%d,%d\n", apt->x, apt->y);
}

int main()
{
	void *mlx = mlx_init();
	int fd;
	t_list *lst;
	t_pack p;
	t_list *path;
	
	p.mlx = mlx;
	if ((fd = open("scene.cub", O_RDONLY)) == -1)
	{
		ft_printf("ERROR ERROR ... FILE YOU MF\n");
		exit(-1);
	}
	lst = file_to_list(fd);
	close(fd);
	parse_all(lst, &p);
	ft_lstclear(&lst, &free);
	t_ipt2d start = {
		.x = 2,
		.y = 1
	};
	t_ipt2d stop = {
		.x = 2,
		.y = 2
	};
	path = update_shortest_path(&p.map, start, stop);
	ft_lstiter(path, &print_ipt2d);
}