/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:25:13 by amaach            #+#    #+#             */
/*   Updated: 2021/01/22 14:58:43 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	help_init_sprite(int i, int k)
{
	int		j;

	while (g_la_map[++i] && (k < g_s_count))
	{
		j = -1;
		while (g_la_map[i][++j] && (k < g_s_count))
		{
			if (g_la_map[i][j] == '2')
			{
				g_sprite[k].x = (float)((j + 0.5) * g_tile_size);
				g_sprite[k].y = (float)((i + 0.5) * g_tile_size);
				g_sprite[k].dist = sqrtf(((g_sprite[k].x) - g_player.x)
					* ((g_sprite[k].x) - g_player.x) + ((g_sprite[k].y)
					- g_player.y) * ((g_sprite[k].y) - g_player.y));
				k++;
			}
		}
	}
}

void	init_sprite(void)
{
	int i;
	int k;

	k = 0;
	i = -1;
	g_sprite = malloc(sizeof(t_sprite) * (g_s_count));
	g_texture.img = mlx_xpm_file_to_image(g_mlx_ptr, g_map.s,
				&g_textures.width, &g_textures.height);
	free(g_map.s);
	if (g_texture.img == 0)
		ft_error_massege("Error\nSprite est vide");
	g_texture.addr = mlx_get_data_addr(g_texture.img,
		&g_texture.bits_per_pixel, &g_texture.line_length, &g_texture.endian);
	help_init_sprite(i, k);
}

void	to_sort(int k)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = -1;
	while (++k < g_s_count)
	{
		g_sprite[k].dist = sqrtf(((g_sprite[k].x) - g_player.x)
			* ((g_sprite[k].x) - g_player.x) + ((g_sprite[k].y) - g_player.y)
			* ((g_sprite[k].y) - g_player.y));
	}
	while (++i < g_s_count - 1)
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
	}
}

void	to_sprite(void)
{
	float	angle;
	int		k;
	float	ray;

	ray = g_rotation * (M_PI / 180);
	k = -1;
	angle = 0;
	to_sort(k);
	while (++k < g_s_count)
	{
		angle = atan2f(g_sprite[k].y - g_player.y, g_sprite[k].x - g_player.x);
		while (angle - ray > M_PI)
			angle -= 2 * M_PI;
		while (angle - ray < -M_PI)
			angle += 2 * M_PI;
		g_sprite[k].size = (float)((g_map.x / g_sprite[k].dist) * 64);
		g_sprite[k].y_off = (float)(g_map.y / 2 - g_sprite[k].size / 2);
		g_sprite[k].x_off = (float)(((((angle * (180 / M_PI)) - g_rotation)
		* g_map.x) / 64) + ((g_map.x / 2) - (int)g_sprite[k].size / 2));
		draw_sprite(k);
	}
}

void	draw_sprite(int id)
{
	int		i;
	int		*tabe;
	float	size;

	i = -1;
	size = g_sprite[id].size;
	tabe = (int*)g_texture.addr;
	while (++i < size - 1)
	{
		if (g_sprite[id].x_off + i <= 0 || g_sprite[id].x_off + i > g_map.x - 1)
			continue ;
		if (g_tab[(int)(g_sprite[id].x_off + i)][0] <= g_sprite[id].dist)
			continue ;
		help_draw_sprite(size, tabe, id, i);
	}
}
