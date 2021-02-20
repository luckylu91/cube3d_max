#ifndef PARSE_H
#define PARSE_H

#include "cub3d.h"

typedef struct	s_parsed_line
{
	int			valid;
	char		*line;
}				t_parsed_line;

typedef int (*t_parse_fun)(t_pack *p, char *line);

typedef struct	s_parse_option
{
	char		*prefix;
	int			mandatory;
	t_parse_fun	parser;
	t_list		*parsed_lines;
}				t_parse_option;

typedef struct	s_lst_parse_map
{
	t_list		*lst;
	int			map_begun;
	t_list		*first_empty;
	int			found_nonempty;
}				t_lst_parse_map;

// file_to_list
t_list	*file_to_list(int fd);
// split_utils
void	free_split(char **splitted);
int		split_error(void);
int		free_split_error(char **splitted);
int		splitlen(char **splitted);
char	**split_and_check_len(char *str, char *delim, int n_fields,
			char *error_message);
// generic_errors
int		malloc_error(void);
int		parse_error(void);
int		message_error(char *message);
// map_errors
int		free_map_error(t_map *map, char **grid, int i);
int		map_error(void);
int		print_invalid_map_error(t_map *map, int i, int j, char *message);
// map_create
int		new_map(t_list *map_lst, t_pack *p);
// image_errors
int		load_sprite_error(t_pack *p);
int		win_image_error(t_pack *p);
int		load_cubeface_error(t_pack *p, int i);
int		file_not_found_error(char *fname);
// image_create
int		colored_image(void *mlx, int color, t_img *res);
int		load_sprite_image(t_pack *p, int type, t_sprite_img *res);
int		funky_image(t_pack *p, t_img *im);
// pack_init
int		pack_init(t_pack *p, void *mlx, int scene_fd);
int		set_win_elements(t_pack *p);
int		load_image(t_pack *p, char *fname, t_img *res);
// textual_check
int		textual_check(t_list *lst, t_list **map_begin);
// params_parse
int				addback_parse_option(t_list **alst, char *prefix,
		int mandatory, t_parse_fun parser);
int				addback_parsed_line(t_list **alst, int valid, char *line);
void	free_parse_option(void *po_ptr);
t_list	*create_po_list(void);
int		recap_po_errors(t_list *po_lst);
int		parse_line(t_list *po_lst, t_pack *p, char *line);
// map_check
int		map_check(t_map *map);
int		parse_all(t_list *lines, t_pack *p, t_list **map_begin);
int		init_sprites(t_pack *p);
int		set_win_elements(t_pack *p);
int		load_const_imgs(t_pack *p);

#endif
