/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:03:49 by amaach            #+#    #+#             */
/*   Updated: 2021/01/14 17:42:00 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int		istheirawall(float x, float y, int k)
{
	int		i;
	int		j;

	if (g_ray.facingleft == 1 && x > 1 && k == 1)
		x--;
	if (g_ray.facingup == 1 && y > 1 && k == 2)
		y--;
	i = floor(y / g_tile_size);
	j = floor(x / g_tile_size);
	if (g_la_map[i][j] == '1' || g_la_map[i][j] == ' ')
		return (1);
	return (0);
}

static void		ft_verti2(float nt_x, float nt_y, float x_stepv, float y_stepv)
{
	while (nt_y >= 0 && nt_y <= g_w_width
			&& nt_x >= 0 && nt_x <= g_w_height)
	{
		if (istheirawall(nt_x, nt_y, 1) == 1)
		{
			g_foundavertiwallhit = 1;
			g_wallhit.verti_x = nt_x;
			g_wallhit.verti_y = nt_y;
			break ;
		}
		else
		{
			nt_y += y_stepv;
			nt_x += x_stepv;
		}
	}
}

void			ft_vertical(float rayangle)
{
	float	x_stepv;
	float	y_stepv;
	float	x_intercept;
	float	y_intercept;

	x_stepv = 0;
	y_stepv = 0;
	x_intercept = 0;
	y_intercept = 0;
	x_intercept = floor(g_player.x / g_tile_size) * g_tile_size;
	if (g_ray.facingright == 1)
		x_intercept += g_tile_size;
	y_intercept = g_player.y + ((x_intercept - g_player.x) * tan(rayangle));
	x_stepv = g_tile_size;
	if (g_ray.facingleft == 1)
		x_stepv *= -1;
	y_stepv = g_tile_size * tan(rayangle);
	if (g_ray.facingup == 1 && y_stepv > 0)
		y_stepv *= -1;
	if (g_ray.facingdown == 1 && y_stepv < 0)
		y_stepv *= -1;
	ft_verti2(x_intercept, y_intercept, x_stepv, y_stepv);
}

static void		ft_horiz2(float nt_x, float nt_y, float x_steph, float y_steph)
{
	while (nt_y >= 0 && nt_y <= g_w_width
			&& nt_x >= 0 && nt_x <= g_w_height)
	{
		if (istheirawall(nt_x, nt_y, 2) == 1)
		{
			g_foundahorizwallhit = 1;
			g_wallhit.horiz_x = nt_x;
			g_wallhit.horiz_y = nt_y;
			break ;
		}
		else
		{
			nt_x += x_steph;
			nt_y += y_steph;
		}
	}
}

void			ft_horizontal(float rayangle)
{
	float	x_steph;
	float	y_steph;
	float	x_intercept;
	float	y_intercept;

	x_steph = 0;
	y_steph = 0;
	x_intercept = 0;
	y_intercept = 0;
	y_intercept = floor(g_player.y / g_tile_size) * g_tile_size;
	if (g_ray.facingdown == 1)
		y_intercept += g_tile_size;
	x_intercept = g_player.x + (y_intercept - g_player.y) / tan(rayangle);
	y_steph = g_tile_size;
	if (g_ray.facingup == 1)
		y_steph *= -1;
	x_steph = g_tile_size / tan(rayangle);
	if (g_ray.facingleft == 1 && x_steph > 0)
		x_steph *= -1;
	if (g_ray.facingright == 1 && x_steph < 0)
		x_steph *= -1;
	ft_horiz2(x_intercept, y_intercept, x_steph, y_steph);
}
