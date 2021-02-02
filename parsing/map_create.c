#include "parse.h"

static void mapline_dimentions(char *line, int *i1, int *i2)
{
	int i;

	i = -1;
	*i1 = -1;
	while (line[++i])
	{
		if (line[i] != ' ' && *i1 == -1)
			*i1 = i;
	}
	i = ft_strlen(line) - 1;
	*i2 = i;
	while (i >= 0 && line[i])
	{
		if (line[i] != ' ' && *i2 == -1)
			*i2 = i;
		i--;
	}
}

void map_dimentions(t_list *map_lst, int *i1, int *i2)
{
	int line_offsets[2];
	int width;
	int height;

	mapline_dimentions(map_lst->content, i1, i2);
	while ((map_lst = map_lst->next))
	{
		mapline_dimentions(map_lst->content, &line_offsets[0], &line_offsets[1]);
		if (line_offsets[0] < *i1)
			*i1 = line_offsets[0];
		if (line_offsets[1] > *i2)
			*i2 = line_offsets[1];
	}
}

static void fill_map_grid(t_list *map_lst, t_map *map, int i1, int i2)
{
	char *mapline;
	int mapline_len;
	int j;
	int i;

	j = 0;
	while (map_lst)
	{
		mapline = map_lst->content;
		mapline_len = ft_strlen(mapline);
		i = i1 - 1;
		while (++i <= i2)
		{
			map->grid[i - i1][j] = i < mapline_len ? mapline[i] : ' ';
		}
		map_lst = map_lst->next;
		j++;
	}
}

int new_map(t_list *map_lst, int i1, int i2, t_map *map)
{
	char **grid;
	int i;
	int height;
	int width;

	height = ft_lstsize(map_lst);
	width = i2 - i1 + 1;
	if (!(map->grid = (char**)ft_array(width, height, sizeof(char))))
		return (map_error());
	if (!(map->pea_sprites_grid = (t_sprite***)ft_array(width, height, sizeof(t_sprite*))))
		return (map_error());
	map->width = width;
	map->height = height;
	map->sprite_count = 0;
	map->enemies_count = 0;
	fill_map_grid(map_lst, map, i1, i2);
	return (1);
}