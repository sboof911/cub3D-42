/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:09:02 by amaach            #+#    #+#             */
/*   Updated: 2021/01/08 17:12:11 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	cddp(float x1, float y1, float x2, float y2)
{
	float	d;

	d = 0;
	d = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
	return (d);
}

void	ft_caldistance(int i)
{
	if (g_foundahorizwallhit == 1)
		g_wallhithorizdist = cddp(g_player.x, g_player.y,
								g_wallhit.horiz_x, g_wallhit.horiz_y);
	else
		g_wallhithorizdist = INT_MAX;
	if (g_foundavertiwallhit == 1)
		g_wallhitvertidist = cddp(g_player.x, g_player.y,
								g_wallhit.verti_x, g_wallhit.verti_y);
	else
		g_wallhitvertidist = INT_MAX;
	if (g_wallhithorizdist < g_wallhitvertidist)
	{
		g_tab[i][0] = g_wallhithorizdist;
		g_tab[i][1] = g_wallhit.horiz_x;
		g_tab[i][2] = g_wallhit.horiz_y;
	}
	else
	{
		g_washitverti = 1;
		g_tab[i][0] = g_wallhitvertidist;
		g_tab[i][1] = g_wallhit.verti_x;
		g_tab[i][2] = g_wallhit.verti_y;
	}
}

void	ft_facing(float k)
{
	if (k > 0 && k < M_PI)
		g_ray.facingdown = 1;
	else if (k != 0 && k != M_PI)
		g_ray.facingup = 1;
	if (k > (M_PI / 2) && k < (3 * M_PI / 2))
		g_ray.facingleft = 1;
	else if (k != (M_PI / 2) && k != (3 * M_PI / 2))
		g_ray.facingright = 1;
}

int		istheirwallside(int i, int j)
{
	if (g_ray.facingup == 1 && g_ray.facingleft == 1)
	{
		if (g_la_map[i][j + 1] == 1 && g_la_map[i + 1][j] == 1)
			return (1);
	}
	return (0);
}

int		istheirawall(float x, float y, int k)
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

void	ft_verti2(float nextvt_x, float nextvt_y, float x_stepv, float y_stepv)
{
	while (nextvt_y >= 0 && nextvt_y <= g_w_width
			&& nextvt_x >= 0 && nextvt_x <= g_w_height)
	{
		if (istheirawall(nextvt_x, nextvt_y, 1) == 1)
		{
			g_foundavertiwallhit = 1;
			g_wallhit.verti_x = nextvt_x;
			g_wallhit.verti_y = nextvt_y;
			break ;
		}
		else
		{
			nextvt_y += y_stepv;
			nextvt_x += x_stepv;
		}
	}
}

void	ft_vertical(float rayangle)
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

void	ft_horiz2(float nextht_x, float nextht_y, float x_steph, float y_steph)
{
	while (nextht_y >= 0 && nextht_y <= g_w_width
			&& nextht_x >= 0 && nextht_x <= g_w_height)
	{
		if (istheirawall(nextht_x, nextht_y, 2) == 1)
		{
			g_foundahorizwallhit = 1;
			g_wallhit.horiz_x = nextht_x;
			g_wallhit.horiz_y = nextht_y;
			break ;
		}
		else
		{
			nextht_x += x_steph;
			nextht_y += y_steph;
		}
	}
}

void	ft_horizontal(float rayangle)
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

void	ft_initialisationray(void)
{
	g_foundahorizwallhit = 0;
	g_foundavertiwallhit = 0;
	g_wallhithorizdist = 0;
	g_wallhitvertidist = 0;
	g_wallhit.horiz_x = 0;
	g_wallhit.horiz_y = 0;
	g_wallhit.verti_x = 0;
	g_wallhit.verti_y = 0;
	g_washitverti = 0;
	g_ray.facingup = 0;
	g_ray.facingdown = 0;
	g_ray.facingleft = 0;
	g_ray.facingright = 0;
	g_ray.facingdown = 0;
	g_ray.facingleft = 0;
	g_ray.facingright = 0;
	g_ray.facingup = 0;
	g_wallhit.x = 0;
	g_wallhit.y = 0;
	g_wallhit.distance = 0;
}

float	ft_raycasting(float k, int i)
{
	float	rota;

	rota = fmod(k, 2 * M_PI);
	ft_initialisationray();
	ft_facing(rota);
	ft_horizontal(rota);
	ft_vertical(rota);
	ft_caldistance(i);
	return (rota);
}
