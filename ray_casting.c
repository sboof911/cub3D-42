/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:09:02 by amaach            #+#    #+#             */
/*   Updated: 2021/01/04 18:51:44 by amaach           ###   ########.fr       */
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
								g_wallhit.Horiz_X, g_wallhit.Horiz_Y);
	else
		g_wallhithorizdist = INT_MAX;
	if (g_foundavertiwallhit == 1)
		g_wallhitvertidist = cddp(g_player.x, g_player.y,
								g_wallhit.Verti_X, g_wallhit.Verti_Y);
	else
		g_wallhitvertidist = INT_MAX;
	if (g_wallhithorizdist < g_wallhitvertidist)
	{
		g_wallhit.distance = g_wallhithorizdist;
		g_wallhit.X = g_wallhit.Horiz_X;
		g_wallhit.Y = g_wallhit.Horiz_Y;
	}
	else
	{
		g_washitverti = 1;
		g_wallhit.distance = g_wallhitvertidist;
		g_wallhit.X = g_wallhit.Verti_X;
		g_wallhit.Y = g_wallhit.Verti_Y;
	}
	g_tab[i][0] = g_wallhit.distance;
	g_tab[i][1] = g_wallhit.X;
	g_tab[i][2] = g_wallhit.Y;
}

void	ft_facing(float k)
{
	if (k > 0 && k < M_PI)
		g_ray.FacingDown = 1;
	else if (k != 0 && k != M_PI)
		g_ray.FacingUp = 1;
	if (k > (M_PI / 2) && k < (3 * M_PI / 2))
		g_ray.FacingLeft = 1;
	else if (k != (M_PI / 2) && k != (3 * M_PI / 2))
		g_ray.FacingRight = 1;
}

int		istheirwallside(int i, int j)
{
	if (g_ray.FacingUp == 1 && g_ray.FacingLeft == 1)
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

	if (g_ray.FacingLeft == 1 && x > 1 && k == 1)
		x--;
	if (g_ray.FacingUp == 1 && y > 1 && k == 2)
		y--;
	i = floor(y / g_tile_size);
	j = floor(x / g_tile_size);
	if (g_la_map[i][j] == '1' || g_la_map[i][j] == ' ')
		return (1);
	return (0);
}

void	ft_vertical(float rayangle)
{
	float	x_stepv;
	float	y_stepv;
	float	x_intercept;
	float	y_intercept;
	float	NextVertiTouch_x;
	float	NextVertiTouch_y;

	x_stepv = 0;
	y_stepv = 0;
	x_intercept = 0;
	y_intercept = 0;
	x_intercept = floor(g_player.x / g_tile_size) * g_tile_size;
	if (g_ray.FacingRight == 1)
		x_intercept += g_tile_size;
	y_intercept = g_player.y + ((x_intercept - g_player.x) * tan(rayangle));
	x_stepv = g_tile_size;
	if (g_ray.FacingLeft == 1)
		x_stepv *= -1;
	y_stepv = g_tile_size * tan(rayangle);
	if (g_ray.FacingUp == 1 && y_stepv > 0)
		y_stepv *= -1;
	if (g_ray.FacingDown == 1 && y_stepv < 0)
		y_stepv *= -1;
	NextVertiTouch_x = x_intercept;
	NextVertiTouch_y = y_intercept;
	while (NextVertiTouch_y >= 0 && NextVertiTouch_y <= g_w_width
			&& NextVertiTouch_x >= 0 && NextVertiTouch_x <= g_w_height)
	{
		if (istheirawall(NextVertiTouch_x, NextVertiTouch_y, 1) == 1)
		{
			g_foundavertiwallhit = 1;
			g_wallhit.Verti_X = NextVertiTouch_x;
			g_wallhit.Verti_Y = NextVertiTouch_y;
			break ;
		}
		else
		{
			NextVertiTouch_y += y_stepv;
			NextVertiTouch_x += x_stepv;
		}
	}
}

void	ft_horizontal(float rayangle)
{
	float	x_steph;
	float	y_steph;
	float	x_intercept;
	float	y_intercept;
	float	NextHorizTouch_x;
	float	NextHorizTouch_y;

	x_steph = 0;
	y_steph = 0;
	x_intercept = 0;
	y_intercept = 0;
	y_intercept = floor(g_player.y / g_tile_size) * g_tile_size;
	if (g_ray.FacingDown == 1)
		y_intercept += g_tile_size;
	x_intercept = g_player.x + (y_intercept - g_player.y) / tan(rayangle);
	y_steph = g_tile_size;
	if (g_ray.FacingUp == 1)
		y_steph *= -1;
	x_steph = g_tile_size / tan(rayangle);
	if (g_ray.FacingLeft == 1 && x_steph > 0)
		x_steph *= -1;
	if (g_ray.FacingRight == 1 && x_steph < 0)
		x_steph *= -1;
	NextHorizTouch_x = x_intercept;
	NextHorizTouch_y = y_intercept;
	while (NextHorizTouch_y >= 0 && NextHorizTouch_y <= g_w_width
			&& NextHorizTouch_x >= 0 && NextHorizTouch_x <= g_w_height)
	{
		if (istheirawall(NextHorizTouch_x, NextHorizTouch_y, 2) == 1)
		{
			g_foundahorizwallhit = 1;
			g_wallhit.Horiz_X = NextHorizTouch_x;
			g_wallhit.Horiz_Y = NextHorizTouch_y;
			break ;
		}
		else
		{
			NextHorizTouch_x += x_steph;
			NextHorizTouch_y += y_steph;
		}
	}
}

void	ft_initialisationray(void)
{
	g_foundahorizwallhit = 0;
	g_foundavertiwallhit = 0;
	g_wallhithorizdist = 0;
	g_wallhitvertidist = 0;
	g_wallhit.Horiz_X = 0;
	g_wallhit.Horiz_Y = 0;
	g_wallhit.Verti_X = 0;
	g_wallhit.Verti_Y = 0;
	g_washitverti = 0;
	g_ray.FacingUp = 0;
	g_ray.FacingDown = 0;
	g_ray.FacingLeft = 0;
	g_ray.FacingRight = 0;
	g_ray.FacingDown = 0;
	g_ray.FacingLeft = 0;
	g_ray.FacingRight = 0;
	g_ray.FacingUp = 0;
	g_wallhit.X = 0;
	g_wallhit.Y = 0;
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
