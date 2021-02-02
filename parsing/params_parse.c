#include "parse.h"

static int parse_resolution(char *line, t_pack *p)
{
	char	**splitted;
	int		width;
	int		height;

	if (!(splitted = split_and_check_len(line, " ", 3)))
	{
		ft_printf("Error\n");
		ft_printf("Error during split in parse_resolution\n");
		ft_printf("Line : %s\n", line);
		return (-1);
	}
	width = ft_atoi(splitted[1]);
	height = ft_atoi(splitted[2]);
	if (width <= 0 || height <= 0)
	{
		ft_printf("Error\n");
		ft_printf("Unvalid width or height in parse_resolution\n");
		ft_printf("Line : %s\n", line);
		return (free_split_error(splitted));
	}
	p->width = width;
	p->height = height;
	free_split(splitted);
	return (0);
}

static int parse_texture_file(char *line, t_pack *p)
{
	char	**splitted;
	char	*fname;
	int		cardinal;

	if (!(splitted = split_and_check_len(line, " ", 2)))
	{
		ft_printf("Error\n");
		ft_printf("Error during split in parse_texture_file\n");
		ft_printf("Line : %s\n", line);
		return (-1);
	}
	fname = ft_strdup(splitted[1]);
	printf("fname = %s\n", fname);
	if (!ft_strncmp(splitted[0], "NO", 2))
		cardinal = NORTH;
	else if (!ft_strncmp(splitted[0], "SO", 2))
		cardinal = SOUTH;
	else if (!ft_strncmp(splitted[0], "WE", 2))
		cardinal = WEST;
	else if (!ft_strncmp(splitted[0], "EA", 2))
		cardinal = EAST;
	else if (!ft_strncmp(splitted[0], "F", 1))
		cardinal = FLOOR;
	else// if (!ft_strncmp(splitted[0], "C", 2))
		cardinal = CEIL;
	p->cube_faces_fnames[cardinal] = fname;
	free_split(splitted);
	return (0);
}

static int parse_color(char *line, t_pack *p)
{
	char	**splitted_line;
	char	**splitted_color;
	int		color;
	int		r;
	int		g;
	int		b;

	if (!(splitted_line = split_and_check_len(line, " ", 2)))
	{
		ft_printf("Error\n");
		ft_printf("Error during split in parse_color (line split)\n");
		ft_printf("Line : %s\n", line);
		return (-1);
	}
	if (!(splitted_color = split_and_check_len(splitted_line[1], " ,", 3)))
	{
		ft_printf("Error\n");
		ft_printf("Error during split in parse_color (rgb split)\n");
		ft_printf("Line : %s\n", line);
		return (free_split_error(splitted_line));
	}
	r = ft_atoi(splitted_color[0]);
	g = ft_atoi(splitted_color[1]);
	b = ft_atoi(splitted_color[2]);
	color = (r << 16) + (g << 8) + b;
	if (!ft_strncmp(splitted_line[0], "F", 2))
		p->floor_color = color;
	else      // if (!ft_strncmp(splitted_line[0], "C", 2))
		p->ceil_color = color;
	free_split(splitted_line);
	free_split(splitted_color);
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
	{
		ft_printf("Error\n");
		ft_printf("One r/g/b value is not in 0-255 range in parse_color\n");
		return (-1);
	}
	return (0);
}

int	parse_iter_fun(char *line, t_pack *p)
{
	static int i = 0;
	int ret;

	if (i == 0)
		ret = parse_resolution(line, p);
	else if (i >= 1 && i <= 5)
		ret = parse_texture_file(line, p);
	else
		ret = parse_color(line, p);
	i++;
	return (ret);
}