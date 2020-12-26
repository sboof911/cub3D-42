/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projecting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:55:59 by amaach            #+#    #+#             */
/*   Updated: 2020/12/26 11:48:00 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	RenderProjectionWall(float k, unsigned int long long str, float rotationAngle)
{
    int     i;
    float   correctdistance;
    float   distanceprojeplane;
    float	WallstripHeight;
	float	WallTopPixel;
	float	WallBotPixel;
    float   RayAngle;

	correctdistance = 0;
	distanceprojeplane = 0;
	WallstripHeight = 0;
	WallTopPixel = 0;
	WallBotPixel = 0;
	RayAngle = 0;
	i = 0;
    RayAngle = k;
    distanceprojeplane = (map.x / 2.0) / tan((FOV * M_PI / 180));
    while (i < map.x)
    {
        RayAngle = ft_RayCasting(RayAngle, i);
        correctdistance = g_tab[i][0] * cos(RayAngle - (rotation * M_PI / 180));
        WallstripHeight = (TILE_SIZE / correctdistance) * distanceprojeplane;
		WallTopPixel = (map.y / 2) -  (WallstripHeight / 2);
		WallBotPixel = (map.y / 2) +  (WallstripHeight / 2);
        if (WallBotPixel > map.y)
            WallBotPixel = map.y;
        if (WallTopPixel < 0)
            WallTopPixel = 0;
		// printf("WalltopPixel = %f\n", WallTopPixel);
		// if (WallTopPixel < 0)
		// 	WallTopPixel = 0;
		// if (WallBotPixel > map.y)
		// 	WallBotPixel = map.y;
        dda(i, WallTopPixel, i , WallBotPixel, str);
        //my_mlx_pixel_put(&img, player.x, player.y, str);
        RayAngle += (FOV * rotationAngle) / map.x;
		i++;
    }
	return (k);
}