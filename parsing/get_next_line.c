/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 00:48:14 by lzins             #+#    #+#             */
/*   Updated: 2021/01/12 15:51:24 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	t_file	*file;

	if (!line)
		return (-1);
	*line = NULL;
	file = file_from_fd(fd);
	return (read_one_line(file, line));
}

t_file	*file_from_fd(int fd)
{
	static t_files_data	f_data = {.len = 0};
	size_t				i;

	i = 0;
	while (i < f_data.len)
	{
		if (f_data.storage[i].fd == fd)
			return (f_data.storage + i);
		i++;
	}
	(f_data.len)++;
	f_data.storage[i].fd = fd;
	f_data.storage[i].head = BUFFER_SIZE;
	return (f_data.storage + i);
}

/*
** Copy the content of buffer in *line (starting from
** the right position if buffer was left non-empty)
** Start by auugmenting the memory area of *line by reallocating
** At the end file->head will either be BUFFER_SIZE,
** either point to '\n' (EOL) or '\0' (EOF approaching)
*/

int		copy_buffer(t_file *file, char **line)
{
	size_t	line_len;
	char	*line_augmented;

	if (*line)
		line_len = ft_strlen(*line);
	else
		line_len = 0;
	if ((line_augmented = malloc(line_len + BUFFER_SIZE + 1)) == NULL)
		return (-1);
	ft_bzero(line_augmented, line_len + BUFFER_SIZE + 1);
	ft_strccpy(line_augmented, *line, '\0', line_len);
	free_safe(*line);
	file->head += ft_strccpy(line_augmented + line_len, file->buffer + file->head,
			'\n', BUFFER_SIZE - file->head);
	*line = line_augmented;
	if (file->buffer[file->head] == '\n')
	{
		(file->head)++;
		return (1);
	}
	if (file->buffer[file->head] == '\0')
		file->head = BUFFER_SIZE;
	return (2);
}

/*
** For each loop pass:
**  - If nothing yet read or all of the current buffer already read,
**     call read() to supply data to the buffer
**  - Copy the (remaining) content of the buffer:
**   + if '\n' was met, end of line and return 1
**   + if '\0' was met, that means the number of bytes read was < BUFFER_SIZE,
**      i.e. the next call of read() should return 0
**      I set file->head to BUFFER_SIZE to trigger this call (this is coherent
**      with the use of "head" (all bytes before aren't relevant anymore)
**   + otherwise the whole buffer was copied and file->head will be equal
**      to BUFFER_SIZE
**  - The previous step can convey the informations :
**     error (-1 i.e. allocation failed) and End Of Line (1)
**  - If end of file was reached, only a subsequent call to read_one_line() will
**     get the EOF signal (0) as expected (n_calls = n_lines + 1)
*/

int		read_one_line(t_file *file, char **line)
{
	ssize_t	br;
	int		step_return;

	br = 1;
	while (br != 0)
	{
		if (file->head == BUFFER_SIZE)
		{
			ft_bzero(file->buffer, BUFFER_SIZE);
			br = read(file->fd, file->buffer, BUFFER_SIZE);
			if (br == -1)
				return (free_safe(*line));
			file->head = 0;
		}
		if ((step_return = copy_buffer(file, line)) == -1)
			return (free_safe(*line));
		if (step_return == 1)
			return (1);
	}
	return (0);
}
