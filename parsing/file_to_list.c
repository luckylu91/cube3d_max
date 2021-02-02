#include "parse.h"
#include "get_next_line.h"

static void	*free_clear_and_error(t_list *lst, char *line)
{
	ft_printf("Error\nDuring scene file reading\n");
	free(line);
	ft_lstclear(&lst, &free);
	return (NULL);
}

static int	ignored_line_filter(char *line)
{
	char	*line_trimmed;
	int		size_trimmed;
	char	first_char;

	if (!(line_trimmed = ft_strtrim(line, " ")))
		return (-1);
	size_trimmed = ft_strlen(line_trimmed);
	first_char = line_trimmed[0];
	free(line_trimmed);
	if (size_trimmed == 0 || first_char == '#')
		return (1);
	return (0);
}

t_list	*file_to_list(int fd)
{
	char	*line;
	t_list	*lst;
	t_list	*new_elem;
	int		ret_gnl;
	int		ret_emptyline;

	lst = NULL;
	line = NULL;
	while ((ret_gnl = get_next_line(fd, &line)) != -1)
	{
		if ((ret_emptyline = ignored_line_filter(line)) == -1)
			return (free_clear_and_error(lst, line));
		if (ret_emptyline == 1)
		{
			free(line);
			continue ;
		}
		if (!(new_elem = ft_lstnew(line)))
			return (free_clear_and_error(lst, line));
		ft_lstadd_back(&lst, new_elem);
		if (ret_gnl == 0)
			return (lst);
	}
	return (free_clear_and_error(lst, line));
}