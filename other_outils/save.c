/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:35:20 by amaach            #+#    #+#             */
/*   Updated: 2021/01/22 10:57:49 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_bzero1(void *s, size_t n)
{
	unsigned int i;

	i = 0;
	if (n)
	{
		while (i < n)
		{
			*(unsigned char*)s = 0;
			s++;
			i++;
		}
	}
}

void	header_initia(void)
{
	g_bmp.type[0] = 0x42;
	g_bmp.type[1] = 0x4D;
	g_bmp.filesize = (g_map.x * g_map.y * 4) + 54;
	g_bmp.reserved1 = 0x00000000;
	g_bmp.reserved2 = 0x00000000;
	g_bmp.pxdataoff = 0x36;
	g_bmp.headersize = 40;
	g_bmp.width = g_map.x;
	g_bmp.height = g_map.y * -1;
	g_bmp.planes = 1;
	g_bmp.bpp = 32;
	g_bmp.compression = 0;
	g_bmp.imagesize = g_map.x * g_map.y * 4;
	g_bmp.xpermeter = 0;
	g_bmp.ypermeter = 0;
	g_bmp.totalcolors = 0;
	g_bmp.importantcolors = 0;
}

void	header_write(int fd)
{
	int			r;

	r = 0;
	r = write(fd, &g_bmp.type, 2);
	r = write(fd, &g_bmp.filesize, 4);
	r = write(fd, &g_bmp.reserved1, 2);
	r = write(fd, &g_bmp.reserved2, 2);
	r = write(fd, &g_bmp.pxdataoff, 4);
	r = write(fd, &g_bmp.headersize, 4);
	r = write(fd, &g_bmp.width, 4);
	r = write(fd, &g_bmp.height, 4);
	r = write(fd, &g_bmp.planes, 2);
	r = write(fd, &g_bmp.bpp, 2);
	r = write(fd, &g_bmp.compression, 4);
	r = write(fd, &g_bmp.imagesize, 4);
	r = write(fd, &g_bmp.xpermeter, 4);
	r = write(fd, &g_bmp.ypermeter, 4);
	r = write(fd, &g_bmp.totalcolors, 4);
	r = write(fd, &g_bmp.importantcolors, 4);
	(void)r;
}

void	write_colors(int fd)
{
	char	*colors;
	int		i;
	int		j;
	int		*color;

	i = 0;
	j = 0;
	color = (int *)g_img.addr;
	if (!(colors = malloc(g_bmp.imagesize * sizeof(char))))
		ft_error_massege("Error\nscreenshot issue");
	while ((u_int32_t)i < g_bmp.imagesize / 4)
	{
		colors[j++] = color[i] & 255;
		colors[j++] = (color[i] & 255 << 8) >> 8;
		colors[j++] = (color[i] & 255 << 16) >> 16;
		colors[j++] = 0;
		i++;
	}
	j = write(fd, colors, g_bmp.imagesize);
	free(colors);
}

void	save_bmp(void)
{
	int		fd;

	if (!((fd = open("screenshot.bmp", O_WRONLY | O_CREAT |
	O_TRUNC, S_IRUSR | S_IWUSR)) > 0))
		ft_error_massege("Error\nscreenshot problem");
	ft_bzero1(&g_bmp, sizeof(t_bmp_file));
	header_initia();
	header_write(fd);
	write_colors(fd);
	close(fd);
	(void)g_bmp;
}
