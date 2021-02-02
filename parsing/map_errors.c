#include "parse.h"

void	free_map(t_map *map)
{
	int i;

	i = -1;
	while (++i < map->width)
		free(map->grid[i]);
	free(map->grid);
}

int		map_error(void)
{
	ft_printf("Error\n");
	ft_printf("Error during map parsing\n");
	return (-1);
}

int free_map_error(t_map *map, char **grid, int i)
{
	free_map(map);
	return (map_error());
}

int print_invalid_map_error(t_map *map, int i, int j)
{
	int di;
	int dj;

	ft_printf("At x=%d, y=%d of map :\n", i, j);
	ft_printf("%5d\u2193\n   -----\n", i);
	dj = -3;
	while(++dj < 3)
	{
		if (dj != 0)
			ft_printf("  |");
		else
			ft_printf("%d\u2192|", i);
		di = -3;
		while (++di < 3)
		{
			if (in_bounds2D(i + di, j + dj, map))
				ft_putchar_fd(map->grid[i + di][j + dj], STDERR_FILENO);
			else
				ft_putchar_fd('.', STDERR_FILENO);
		}
		ft_printf("|\n");
	}
	ft_printf("   -----\n");
	return (-1);
}