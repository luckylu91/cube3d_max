#include "parse.h"

void free_split(char **splitted)
{
	int i;

	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

int free_split_error(char **splitted)
{
	free_split(splitted);
	return (-1);
}

int splitlen(char **splitted)
{
	int i;

	i = 0;
	while (splitted[i])
		i++;
	return (i);
}

char	**split_and_check_len(char *str, char *delim, int n_fields)
{
	char	**splitted;

	if (!(splitted = ft_split(str, delim)))
		return (NULL);
	if (splitlen(splitted) != n_fields)
	{
		free_split(splitted);
		return (NULL);
	}
	return (splitted);
}