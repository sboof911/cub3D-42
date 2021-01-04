/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:09:02 by amaach            #+#    #+#             */
/*   Updated: 2021/01/04 17:53:10 by amaach           ###   ########.fr       */
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
	if (FoundAHorizWallHit == 1)
		WallHitHorizDistance = cddp(player.x, player.y,
								WallHit.Horiz_X, WallHit.Horiz_Y);
	else
		WallHitHorizDistance = INT_MAX;
	if (FoundAVertiWallHit == 1)
		g_wallhitvertidist = cddp(player.x, player.y,
								WallHit.Verti_X, WallHit.Verti_Y);
	else
		g_wallhitvertidist = INT_MAX;
	if (WallHitHorizDistance < g_wallhitvertidist)
	{
		WallHit.Distance = WallHitHorizDistance;
		WallHit.X = WallHit.Horiz_X;
		WallHit.Y = WallHit.Horiz_Y;
	}
	else
	{
		WasHitVerti = 1;
		WallHit.Distance = g_wallhitvertidist;
		WallHit.X = WallHit.Verti_X;
		WallHit.Y = WallHit.Verti_Y;
	}
	g_tab[i][0] = WallHit.Distance;
	g_tab[i][1] = WallHit.X;
	g_tab[i][2] = WallHit.Y;
}

void	ft_facing(float k)
{
	if (k > 0 && k < M_PI)
		Ray.FacingDown = 1;
	else if (k != 0 && k != M_PI)
		Ray.FacingUp = 1;
	if (k > (M_PI / 2) && k < (3 * M_PI / 2))
		Ray.FacingLeft = 1;
	else if (k != (M_PI / 2) && k != (3 * M_PI / 2))
		Ray.FacingRight = 1;
}

int		istheirwallside(int i, int j)
{
	if (Ray.FacingUp == 1 && Ray.FacingLeft == 1)
	{
		if (la_map[i][j + 1] == 1 && la_map[i + 1][j] == 1)
			return (1);
	}
	return (0);
}

int		istheirawall(float x, float y, int k)
{
	int		i;
	int		j;

	if (Ray.FacingLeft == 1 && x > 1 && k == 1)
		x--;
	if (Ray.FacingUp == 1 && y > 1 && k == 2)
		y--;
	i = floor(y / TILE_SIZE);
	j = floor(x / TILE_SIZE);
	if (la_map[i][j] == '1' || la_map[i][j] == ' ')
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
	x_intercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
	if (Ray.FacingRight == 1)
		x_intercept += TILE_SIZE;
	y_intercept = player.y + ((x_intercept - player.x) * tan(rayangle));
	x_stepv = TILE_SIZE;
	if (Ray.FacingLeft == 1)
		x_stepv *= -1;
	y_stepv = TILE_SIZE * tan(rayangle);
	if (Ray.FacingUp == 1 && y_stepv > 0)
		y_stepv *= -1;
	if (Ray.FacingDown == 1 && y_stepv < 0)
		y_stepv *= -1;
	NextVertiTouch_x = x_intercept;
	NextVertiTouch_y = y_intercept;
	while (NextVertiTouch_y >= 0 && NextVertiTouch_y <= WINDOW_WIDTH
			&& NextVertiTouch_x >= 0 && NextVertiTouch_x <= WINDOW_HIGHT)
	{
		if (istheirawall(NextVertiTouch_x, NextVertiTouch_y, 1) == 1)
		{
			FoundAVertiWallHit = 1;
			WallHit.Verti_X = NextVertiTouch_x;
			WallHit.Verti_Y = NextVertiTouch_y;
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
	y_intercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	if (Ray.FacingDown == 1)
		y_intercept += TILE_SIZE;
	x_intercept = player.x + (y_intercept - player.y) / tan(rayangle);
	y_steph = TILE_SIZE;
	if (Ray.FacingUp == 1)
		y_steph *= -1;
	x_steph = TILE_SIZE / tan(rayangle);
	if (Ray.FacingLeft == 1 && x_steph > 0)
		x_steph *= -1;
	if (Ray.FacingRight == 1 && x_steph < 0)
		x_steph *= -1;
	NextHorizTouch_x = x_intercept;
	NextHorizTouch_y = y_intercept;
	while (NextHorizTouch_y >= 0 && NextHorizTouch_y <= WINDOW_WIDTH
			&& NextHorizTouch_x >= 0 && NextHorizTouch_x <= WINDOW_HIGHT)
	{
		if (istheirawall(NextHorizTouch_x, NextHorizTouch_y, 2) == 1)
		{
			FoundAHorizWallHit = 1;
			WallHit.Horiz_X = NextHorizTouch_x;
			WallHit.Horiz_Y = NextHorizTouch_y;
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
	FoundAHorizWallHit = 0;
	FoundAVertiWallHit = 0;
	WallHitHorizDistance = 0;
	g_wallhitvertidist = 0;
	WallHit.Horiz_X = 0;
	WallHit.Horiz_Y = 0;
	WallHit.Verti_X = 0;
	WallHit.Verti_Y = 0;
	WasHitVerti = 0;
	Ray.FacingUp = 0;
	Ray.FacingDown = 0;
	Ray.FacingLeft = 0;
	Ray.FacingRight = 0;
	Ray.FacingDown = 0;
	Ray.FacingLeft = 0;
	Ray.FacingRight = 0;
	Ray.FacingUp = 0;
	WallHit.X = 0;
	WallHit.Y = 0;
	WallHit.Distance = 0;
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
