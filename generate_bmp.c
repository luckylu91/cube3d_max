/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_bmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzins <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:43:55 by hgallien          #+#    #+#             */
/*   Updated: 2021/02/17 13:45:24 by lzins            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	write_number(int fd, int nb, int n_oct)
{
	char buff;

	while (--n_oct >= 0)
	{
		buff = nb & 0xff;
		nb = nb >> 8;
		write(fd, &buff, 1);
	}
}

static void	bmp_header_file(int fd, t_pack *p)
{
	write(fd, "BM", 2);
	write_number(fd, 3 * p->width * p->height + 54, 4);
	write_number(fd, 0, 2);
	write_number(fd, 0, 2);
	write_number(fd, 54, 4);
}

static void	bmp_header_img(int fd, t_pack *p)
{
	write_number(fd, 40, 4);
	write_number(fd, p->width, 4);
	write_number(fd, p->height, 4);
	write_number(fd, 1, 2);
	write_number(fd, 24, 2);
	write_number(fd, 0, 4);
	write_number(fd, 3 * p->width * p->height, 4);
	write_number(fd, 0, 4);
	write_number(fd, 0, 4);
	write_number(fd, 0, 4);
	write_number(fd, 0, 4);
}

static void	bmp_by_pixel(int fd, t_pack *p, t_img *im)
{
	int i;
	int j;

	j = p->height;
	while (--j >= 0)
	{
		i = -1;
		while (++i < p->width)
			write_number(fd, *get_pix_address(im, i, j), 3);
	}
}

int			generate_bmp(char *fname, t_pack *p)
{
	int fd;

	render(p);
	if ((fd = open(fname, O_CREAT | O_RDWR, 0666)) < 0)
		return (file_error(fname));
	bmp_header_file(fd, p);
	bmp_header_img(fd, p);
	bmp_by_pixel(fd, p, buff_img(p));
	if (close(fd) < 0)
		return (file_error(fname));
	return (1);
}
