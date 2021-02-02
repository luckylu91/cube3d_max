#include "parse.h"


int	parse_all(t_list *lst, t_pack *p)
{
	t_list *map_begin;
	int i1;
	int i2;

	if (textual_check(lst, &map_begin) == -1)
		return (parse_error());
	while ((lst != map_begin) && lst)
	{
		if (parse_iter_fun(lst->content, p) == -1)
			return (parse_error());
		lst = lst->next;
	}
	map_dimentions(map_begin, &i1, &i2);
	if (new_map(map_begin, i1, i2, &p->map) == -1)
		return (parse_error());
	if (map_check(&p->map) == -1)
	{
		ft_printf("Error\n");
		ft_printf("Map is invalid\n");
		return (parse_error());
	}
	// if (!(p->sprites = ft_calloc(p->map.sprite_count, sizeof(t_sprite)))
	// 		|| !(p->enemies = ft_calloc(p->map.enemies_count, sizeof(t_sprite))))
	// {
	// 	ft_printf("Error\n");
	// 	ft_printf("Malloc error for p->dist_array\n");
	// 	return (parse_error());
	// }
	if (!(p->dist_array = (double**)ft_array(p->width, p->height, sizeof(double))))
	{
		ft_printf("Error\n");
		ft_printf("Malloc error for p->dist_array\n");
		return (parse_error());
	}
	if (set_cube_faces_sprites(p) == -1
		|| set_map_objects_sprites(p) == -1
		|| set_win_elements(p) == -1)
		return (parse_error());
	return (0);
}