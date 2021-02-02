#include "parse.h"

static int prefix_check(char *line)
{
	static char	*prefixes[8] = {"R ", "NO ", "SO ", "WE ", "EA ", "S ", "F ", "C "};
	static int	i = 0;

	if (i >= 8)
		return (0);
	if (ft_strncmp(line, prefixes[i], ft_strlen(prefixes[i])))
	{
		ft_printf("Error\n");
		ft_printf("%sparameter is not present or at the wrong", prefixes[i]);
		ft_printf("Line (argument number %i)\n", i + 1);
		ft_printf("Found : %s\n", line);
		return (-1);
	}
	i++;
	return (1);
}

static int mapline_check(char *line)
{
	int begining;
	int i;
	int player_start_found;

	player_start_found = 0;
	begining = 1;
	i = -1;
	while (line[++i])
	{
		if (!ft_strchr(MAP_CHARS, line[i]))
		{
			ft_printf("Error\n");
			ft_printf("Forbidden character in map line \"%s\" -> %c\n",
				line, line[i]);
			return (-1);
		}
	}
	return (1);
}

int textual_check(t_list *lst, t_list **map_begin)
{
	int ret;

	ret = 1;
	while (lst && ret)
	{
		if ((ret = prefix_check(lst->content)) == -1)
			return (-1);
		*map_begin = lst;
		lst = lst->next;
	}
	if (!lst)
		return (-1);
	while (lst)
	{
		if (mapline_check(lst->content) == -1)
			return (-1);
		lst = lst->next;
	}
	return (1);
}