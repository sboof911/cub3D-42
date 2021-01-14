/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otherhelp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:20:44 by amaach            #+#    #+#             */
/*   Updated: 2021/01/14 10:18:07 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			help_draw_sprite(float size, int *tabe, int id, int i)
{
	int		j;
	int		c;

	j = -1;
	while (++j < size - 1)
	{
		if (g_sprite[id].y_off + j <= 0
			|| g_sprite[id].y_off + j > g_map.y - 1)
			continue ;
		c = tabe[(int)((64) * (64 * j / (int)size) + (64 * i / (int)size))];
		if (c != tabe[0])
			my_mlx_pixel_put(i + g_sprite[id].x_off,
				j + g_sprite[id].y_off, c);
	}
}

void			dda(float x0, float y0, float x1, float y1)
{
	float	x;
	float	y;
	int		i;
	int		str;

	i = 0;
	g_dda.dx = x1 - x0;
	g_dda.dy = y1 - y0;
	g_dda.steps = abs(g_dda.dx) > abs(g_dda.dy) ? abs(g_dda.dx) : abs(g_dda.dy);
	if (g_dda.compt == 1)
		str = g_ceil.color;
	if (g_dda.compt == 2)
		str = g_floor.color;
	if (g_dda.steps < 1)
		g_dda.steps = 1;
	g_dda.xinc = g_dda.dx / (float)g_dda.steps;
	g_dda.yinc = g_dda.dy / (float)g_dda.steps;
	x = x0;
	y = y0;
	while (i++ <= g_dda.steps)
	{
		my_mlx_pixel_put(x, y, str);
		x += g_dda.xinc;
		y += g_dda.yinc;
	}
}

void			draw_player(void)
{
	int		i;
	float	k;
	float	rotationangle;
	float	movespeed;
	float	rotationspeed;

	g_numberofrays = g_map.x;
	movespeed = 2;
	i = 0;
	rotationangle = M_PI / 180;
	rotationspeed = 2 * g_turn_direction;
	g_rotation += rotationspeed;
	k = (g_rotation - 30) * rotationangle;
	if (g_rotation < 0)
		g_rotation += 360;
	g_rotation = fmod(g_rotation, 360);
	if (g_player.x == 0 && g_player.y == 0)
	{
		g_player.x = g_position.x + g_tile_size / 2;
		g_player.y = g_position.y + g_tile_size / 2;
	}
	renderprojectionwall(k, rotationangle);
}

void			ft_draw_map(void)
{
	int		i;
	int		j;

	i = -1;
	while (g_la_map[++i] != '\0')
	{
		g_position.x = 0;
		j = -1;
		while (g_la_map[i][++j] != '\0')
		{
			if ((g_la_map[i][j] == 'N' || g_la_map[i][j] == 'W'
			|| g_la_map[i][j] == 'S' || g_la_map[i][j] == 'E')
			&& g_check_playerdraw == 0)
			{
				ft_checkdirectionplayer(i, j);
				draw_player();
				g_check_playerdraw++;
			}
			g_position.x = g_position.x + g_tile_size;
		}
		g_position.y = g_position.y + g_tile_size;
	}
	if (g_check_playerdraw == 0)
		ft_error_massege("Error\nposition player not found");
}
