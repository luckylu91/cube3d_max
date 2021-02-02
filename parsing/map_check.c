#include "parse.h"

static int map_check_one(t_map *map, int i, int j)
{
	int di;
	int dj;

	di = -2;
	while (++di < 2)
	{
		dj = -2;
		while (++dj < 2)
		{
			if (di == 0 && dj == 0)
				continue ;
			if (in_bounds2D(i + di, j + dj, map)
					&& map->grid[i][j] == OUTSIDE
					&& map->grid[i + di][j + dj] != WALL
					&& map->grid[i + di][j + dj] != OUTSIDE)
				return (-1);
			if (!in_bounds2D(i + di, j + dj, map)
					&& map->grid[i][j] != OUTSIDE
					&& map->grid[i][j] != WALL)
				return (-1);
		}
	}
	return (1);
}

int map_check(t_map *map)
{
	int i;
	int j;
	int n_player_start;

	n_player_start = 0;
	i = -1;
	while (++i < map->width)
	{
		j = -1;
		while (++j < map->height)
		{
			if (map_check_one(map, i, j) == -1)
			{
				ft_printf("Error\n");
				return (print_invalid_map_error(map, i, j));
			}
			if (ft_strchr("NSWE", map->grid[i][j]))
				n_player_start++;
			if (n_player_start > 1)
			{
				ft_printf("Error\n");
				ft_printf("At least two player-start given. Here is the second one found :\n");
				return (print_invalid_map_error(map, i, j));
			}
			if (ft_strchr(SPRITES, map->grid[i][j]))
				map->sprite_count++;
			if (ft_strchr(ENEMIES, map->grid[i][j]))
				map->enemies_count++;
		}
	}
	if (n_player_start == 0)
	{
		ft_printf("Error\n");
		ft_printf("No player-start found (N/S/W/E character)\n");
		return (-1);
	}
	return (1);
}