/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:09:02 by amaach            #+#    #+#             */
/*   Updated: 2020/12/25 12:23:04 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	CalculDistanceDeuxPoints(float x1, float y1, float x2, float y2)
{
	float	D;

	D = 0;
	D = sqrt(((x2 - x1) * (x2 - x1))+((y2 - y1) * (y2 - y1)));
	return (D);
}

void    ft_CalDistance(int i)
{
    if (FoundAHorizWallHit == 1)
	    WallHitHorizDistance = CalculDistanceDeuxPoints(player.x, player.y, WallHit.Horiz_X, WallHit.Horiz_Y);
    else
    	WallHitHorizDistance = INT_MAX;
    if (FoundAVertiWallHit == 1)
	    WallHitVertiDistance = CalculDistanceDeuxPoints(player.x, player.y, WallHit.Verti_X, WallHit.Verti_Y);
	else
        WallHitVertiDistance = INT_MAX;
    if (WallHitHorizDistance < WallHitVertiDistance)
	{
		WallHit.Distance = WallHitHorizDistance;
		WallHit.X = WallHit.Horiz_X;
		WallHit.Y = WallHit.Horiz_Y;
	}
	else
	{
		WasHitVerti = 1;
		WallHit.Distance = WallHitVertiDistance;
		WallHit.X = WallHit.Verti_X;
		WallHit.Y = WallHit.Verti_Y;
	}
    g_tab[i][0] = WallHit.Distance;
    g_tab[i][1] = WallHit.X;
    g_tab[i][2] = WallHit.Y;
}

void    ft_facing(float k)
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

int     IsTheirWallSide(int i, int j)
{
    if (Ray.FacingUp == 1 && Ray.FacingLeft == 1)
	{
		if (la_map[i][j + 1] == 1 && la_map[i + 1][j] == 1)
		return 1;
	}
    return 0;
}

int		IsTheirAWall(float x, float y, int k)
{
	int		i;
	int		j;

	if (Ray.FacingLeft == 1 && x > 1 && k == 1)
		x--;
	if (Ray.FacingUp == 1 && y > 1 && k == 2)
		y--;
	i = floor(y / TILE_SIZE);
	j = floor(x / TILE_SIZE);
    // if (IsTheirWallSide(i, j) == 1)
    //     return (1);
	if (la_map[i][j] == '1' || la_map[i][j] == ' ')
		return (1);
	return (0);
}

void    ft_vertical(float RayAngle)
{
    float	x_stepV;
    float	y_stepV;
    float	x_intercept;
    float	y_intercept;
    float	NextVertiTouch_x;
    float	NextVertiTouch_y;

    x_stepV = 0;
    y_stepV = 0;
    x_intercept = 0;
    y_intercept = 0;
    x_intercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
    if (Ray.FacingRight == 1)
        x_intercept += TILE_SIZE;
    y_intercept = player.y + ((x_intercept - player.x) * tan(RayAngle));
    x_stepV = TILE_SIZE;
    if (Ray.FacingLeft == 1)
        x_stepV *= -1;
    y_stepV = TILE_SIZE * tan(RayAngle);
    if (Ray.FacingUp == 1 && y_stepV > 0)
        y_stepV *= -1;
    if (Ray.FacingDown == 1 && y_stepV < 0)
        y_stepV *= -1;
    NextVertiTouch_x = x_intercept;
    NextVertiTouch_y = y_intercept;
    // if (Ray.FacingLeft == 1)
    //     NextVertiTouch_x--;
    while (NextVertiTouch_y >= 0 && NextVertiTouch_y <= WINDOW_WIDTH
            && NextVertiTouch_x >= 0 && NextVertiTouch_x <= WINDOW_HIGHT)
    {
        //printf("y = %f & x = %f\n", NextVertiTouch_y, NextVertiTouch_x);
        if (IsTheirAWall(NextVertiTouch_x, NextVertiTouch_y, 1) == 1)
        {
            // if (Ray.FacingLeft == 1)
            //     NextVertiTouch_x++;
            FoundAVertiWallHit = 1;
            WallHit.Verti_X = NextVertiTouch_x;
            WallHit.Verti_Y = NextVertiTouch_y;
            break;
        }
        else
        {
            NextVertiTouch_y += y_stepV;
            NextVertiTouch_x += x_stepV;
        }
    }
}

void    ft_horizontal(float RayAngle)
{
    float	x_stepH;
    float	y_stepH;
    float	x_intercept;
    float	y_intercept;
    float	NextHorizTouch_x;
    float	NextHorizTouch_y;

    x_stepH = 0;
    y_stepH = 0;
    x_intercept = 0;
    y_intercept = 0;
    y_intercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
    if (Ray.FacingDown == 1)
        y_intercept += TILE_SIZE;
    x_intercept = player.x + (y_intercept - player.y) / tan(RayAngle);
    y_stepH = TILE_SIZE;
    if (Ray.FacingUp == 1)
        y_stepH *= -1;
    x_stepH = TILE_SIZE / tan(RayAngle);
    if (Ray.FacingLeft == 1 && x_stepH > 0)
        x_stepH *= -1;
    if (Ray.FacingRight == 1 && x_stepH < 0)
		x_stepH *= -1;
	NextHorizTouch_x = x_intercept;
    NextHorizTouch_y = y_intercept;
    // if (Ray.FacingUp == 1)
    //     NextHorizTouch_y--;
    while (NextHorizTouch_y >= 0 && NextHorizTouch_y <= WINDOW_WIDTH
            && NextHorizTouch_x >= 0 && NextHorizTouch_x <= WINDOW_HIGHT)
    {
        //printf("y = %f & x = %f\n", NextHorizTouch_y, NextHorizTouch_x);
        if (IsTheirAWall(NextHorizTouch_x, NextHorizTouch_y, 2) == 1)
        {
            // if (Ray.FacingUp == 1)
            //     NextHorizTouch_y++;
            FoundAHorizWallHit = 1;
            WallHit.Horiz_X = NextHorizTouch_x;
            WallHit.Horiz_Y = NextHorizTouch_y;
            break;
        }
        else
        {
			NextHorizTouch_x += x_stepH;
            NextHorizTouch_y += y_stepH;
        }
    }
}

void	ft_initialisationRay(void)
{
	FoundAHorizWallHit = 0;
	FoundAVertiWallHit = 0;
	WallHitHorizDistance = 0;
	WallHitVertiDistance = 0;
	WallHit.Horiz_X = 0;
	WallHit.Horiz_Y = 0;
	WallHit.Verti_X =0;
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

float   ft_RayCasting(float k, int i)
{
    float	rota;

    rota = fmod(k, 2 * M_PI);
    // if (rota < 0)
    //     rota += 2 * M_PI;
    // if (rota > 2 * M_PI)
	// 	rota -= 2 * M_PI;
	ft_initialisationRay();
    ft_facing(rota);
    ft_horizontal(rota);
    ft_vertical(rota);
	ft_CalDistance(i);
    return (rota);
}