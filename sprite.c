/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:25:13 by amaach            #+#    #+#             */
/*   Updated: 2021/01/04 17:02:42 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_sprite(void)
{
    int i;
    int j;
    int k;
	int w;
	int h;
    
    k = 0;
    i = -1;
    g_sprite  = malloc(sizeof(t_sprite) * (g_s_count));
    texture.img = mlx_xpm_file_to_image(g_mlx_ptr, map.S, &textures.width, &textures.height);
    texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel, &texture.line_length, &texture.endian);
    while(la_map[++i] && (k < g_s_count))
    {
		j = -1;
        while(la_map[i][++j] && (k < g_s_count))
        {
            if(la_map[i][j] == '2')
            {
                g_sprite[k].x = (float)((j + 0.5) * 64);
                g_sprite[k].y = (float)((i + 0.5) * 64);
                g_sprite[k].dist = sqrtf(((g_sprite[k].x) - player.x) * ((g_sprite[k].x)
					- player.x) + ((g_sprite[k].y) - player.y) * ((g_sprite[k].y) - player.y));
				k++;
            }
        }
    }
}

void	to_sort(void)
{
	int				i;
	int				j;
	t_sprite		tmp;
	i = 0;
	while (i < g_s_count - 1)
	{
		j = i;
		while (j < g_s_count - 1)
		{
			if (g_sprite[j].dist < g_sprite[j + 1].dist)
			{
				tmp = g_sprite[j];
				g_sprite[j] = g_sprite[j + 1];
				g_sprite[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void    to_sprite(void)
{
    float   angle;
    int     k;
    int     i;

    k = -1;
    i = 0;
    angle = 0;
    to_sort();
    while(++k < g_s_count)
    {
        g_sprite[k].dist = sqrtf(((g_sprite[k].x) - player.x) * ((g_sprite[k].x)
					- player.x) + ((g_sprite[k].y) - player.y) * ((g_sprite[k].y) - player.y));
        angle = atan2f(g_sprite[k].y - player.y, g_sprite[k].x - player.x);
        while (angle - (rotation * (M_PI / 180)) > M_PI)
			angle -= 2 * M_PI;
		while (angle - (rotation * (M_PI / 180)) < -M_PI)
			angle += 2 * M_PI;
        g_sprite[k].size = (float)((map.x / g_sprite[k].dist) * 64);
		g_sprite[k].y_off = (float)(map.y / 2 - g_sprite[k].size / 2);
		g_sprite[k].x_off = (float)((((angle * (180 / M_PI)) - rotation) * map.x)
		/ 64 + ((map.x / 2) - (int)g_sprite[k].size / 2));
		draw_sprite(k);
    }
}

void    draw_sprite(int id)
{
    int		i;
	int		j;
	int		c;
    int     *tabe;
	float	size;

	i = -1;
	size = g_sprite[id].size;
    tabe = (int*)texture.addr;
    while (++i < size - 1)
	{
		if (g_sprite[id].x_off + i <= 0 || g_sprite[id].x_off + i > map.x - 1)
			continue ;
		if (g_tab[(int)(g_sprite[id].x_off + i)][0] <= g_sprite[id].dist)
			continue ;
	 	j = -1;
		while (++j < size - 1)
		{
			if (g_sprite[id].y_off + j <= 0 || g_sprite[id].y_off + j > map.y - 1)
				continue ;
			c = tabe[(int)((64) * (64 * j / (int)size) + (64 * i / (int)size))];
			if (c != tabe[0])
                my_mlx_pixel_put(&img, i + g_sprite[id].x_off ,j + g_sprite[id].y_off, c);
		}
	}
}