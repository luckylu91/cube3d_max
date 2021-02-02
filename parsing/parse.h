#ifndef PARSE_H
#define PARSE_H

#include "cub3d.h"

typedef struct		s_parameter
{
	int				code;
	char			*str_value;
}					t_parameter;

// file_to_list
t_list	*file_to_list(int fd);
// split_utils
int		splitlen(char **splitted);
char	**split_and_check_len(char *str, char *delim, int n_fields);
void	free_split(char **splitted);
int		free_split_error(char **splitted);
// generic_errors
int		malloc_error(void);
int		parse_error(void);
// map_errors
int		free_map_error(t_map *map, char **grid, int i);
void	free_map(t_map *map);
int		map_error(void);
int		print_invalid_map_error(t_map *map, int i, int j);
// map_create
void	map_dimentions(t_list *map_lst, int *i1, int *i2);
int		new_map(t_list *map_lst, int i1, int i2, t_map *map);
// image_errors
int		load_sprite_error(t_pack *p);
int		win_image_error(t_pack *p);
int		load_cubeface_error(t_pack *p, int i);
// image_create
int		colored_image(void *mlx, int color, t_img *res);
int		load_sprite_image(void *mlx, int type, t_sprite_img *res);
// map_objects_init
int		set_map_objects_sprites(t_pack *p);
// pack_init
int		init(t_pack *p, void *mlx, char *scene_path);
int		set_win_elements(t_pack *p);
int		set_cube_faces_sprites(t_pack *p);
// textual_check
int		textual_check(t_list *lst, t_list **map_begin);
// params_parse
int		parse_iter_fun(char *line, t_pack *p);
// map_check
int		map_check(t_map *map);
int		parse_all(t_list *lst, t_pack *p);

#endif