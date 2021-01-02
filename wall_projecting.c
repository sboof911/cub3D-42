/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projecting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:55:59 by amaach            #+#    #+#             */
/*   Updated: 2020/12/31 11:52:46 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_texture(int textureoffset_x, int textureoffset_y, int i, float y)
{
	int		color;
	if (WasHitVerti == 1)
	{
		if (Ray.FacingLeft)
			color = textures.ea[(textures.width * textureoffset_y) + textureoffset_x];
		else
			color = textures.we[(textures.width * textureoffset_y) + textureoffset_x];
	}
	else
	{
		if (Ray.FacingUp)
			color = textures.no[(textures.width * textureoffset_y) + textureoffset_x];
		else
			color = textures.so[(textures.width * textureoffset_y) + textureoffset_x];
	}
	my_mlx_pixel_put(&img, i, y, color);
}

void    ft_textures(int i, float walltoppixel, float wallbotpixel, float wallstripheight)
{
	int		textureoffset_x;
	int		textureoffset_y;
    float	y;
	float	distancefromtop;

    y = (int) walltoppixel;
	if (WasHitVerti)
		textureoffset_x = (int)g_tab[i][2] % TILE_SIZE;
	else
		textureoffset_x = (int)g_tab[i][1] % TILE_SIZE;
    while (y < wallbotpixel)
    {
		distancefromtop = y + (wallstripheight / 2) - (map.y / 2);
		textureoffset_y = distancefromtop * ((float)textures.height / wallstripheight);
		ft_check_texture(textureoffset_x, textureoffset_y, i, y);
		y++;
    }
}

float	RenderProjectionWall(float k, unsigned int long long str, float rotationAngle)
{
    int     i;
    float   correctdistance;
    float   distanceprojeplane;
    float	wallstripheight;
	float	walltoppixel;
	float	wallbotpixel;
    float   rayangle;

	correctdistance = 0;
	distanceprojeplane = 0;
	wallstripheight = 0;
	walltoppixel = 0;
	wallbotpixel = 0;
	rayangle = 0;
	i = 0;
    rayangle = k;
    distanceprojeplane = (map.x / 2.0) / tan((FOV * M_PI / 180) / 2);
    while (i < map.x)
    {
        rayangle = ft_RayCasting(rayangle, i);
        correctdistance = g_tab[i][0] * cos(rayangle - (rotation * M_PI / 180));
        wallstripheight = (TILE_SIZE / correctdistance) * distanceprojeplane;
		walltoppixel = (map.y / 2) -  (wallstripheight / 2);
		wallbotpixel = (map.y / 2) +  (wallstripheight / 2);
        if (wallbotpixel > map.y)
            wallbotpixel = map.y;
        if (walltoppixel < 0)
            walltoppixel = 0;
        dda(i, 0, i, walltoppixel, C.color);
		ft_textures(i, walltoppixel, wallbotpixel, wallstripheight);
        dda(i, wallbotpixel, i, map.y, F.color);
        rayangle += (FOV * rotationAngle) / map.x;
		i++;
    }
	return (k);
}