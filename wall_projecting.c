/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projecting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:55:59 by amaach            #+#    #+#             */
/*   Updated: 2020/12/18 12:59:53 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	RenderProjectionWall(float k, unsigned int long long str, float rotationAngle)
{
    int     i;
    float   raydistance;
    float   distanceprojeplane;
    float	WallstripHeight;
	float	WallTopPixel;
	float	WallBotPixel;
    float   Angle;
    
    Angle = ((FOV * rotationAngle) / g_numberofrays);
    distanceprojeplane = (map.x / 2) / tan(FOV / 2);
    i = 0;
    while (i < g_numberofrays)
    {
        ft_RayCasting(k, i);
        raydistance = g_tab[i][0];
        WallstripHeight = (TILE_SIZE / g_tab[i][0]) * distanceprojeplane;
		WallTopPixel = (map.y / 2) -  (WallstripHeight / 2);
		WallBotPixel = (map.y / 2) +  (WallstripHeight / 2);
		// if (WallTopPixel < 0)
		// 	WallTopPixel = 0;
		// if (WallBotPixel > map.y)
		// 	WallBotPixel = map.y;
        dda(i, WallTopPixel, i , WallBotPixel, str);
        //my_mlx_pixel_put(&img, player.x, player.y, str);
        k += Angle;
		i++;
    }
	return (k);
}