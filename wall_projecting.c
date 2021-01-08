/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projecting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:55:59 by amaach            #+#    #+#             */
/*   Updated: 2021/01/08 12:20:21 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_texture(int toffset_x, int toffset_y, int i, float y)
{
	int		color;
	int		d;

	d = (64 * toffset_y) + toffset_x;
	if (d < 0)
		d = abs(d);
	if (d >= 64 * 64)
		d = 64 * 63;
	if (g_washitverti == 1)
	{
		if (g_ray.facingleft)
			color = g_textures.ea[d];
		else
			color = g_textures.we[d];
	}
	else
	{
		if (g_ray.facingup)
			color = g_textures.no[d];
		else
			color = g_textures.so[d];
	}
	my_mlx_pixel_put(i, y, color);
}

void	ft_textures(int i, float walltop, float wallbot, float wallstripheight)
{
	int		textureoffset_x;
	int		textureoffset_y;
	float	y;
	float	distancefromtop;

	y = (int)walltop;
	if (g_washitverti)
		textureoffset_x = (int)g_tab[i][2] % g_tile_size;
	else
		textureoffset_x = (int)g_tab[i][1] % g_tile_size;
	while (y < wallbot)
	{
		distancefromtop = y + (wallstripheight / 2) - (g_map.y / 2);
		textureoffset_y = distancefromtop *
						((float)64 / wallstripheight);
		ft_check_texture(textureoffset_x, textureoffset_y, i, y);
		y++;
	}
}

float	renderprojectionwall(float k, float rotationangle)
{
	int		i;
	float	corrdist;
	float	distanceprojeplane;
	float	wallstripheight;
	float	walltoppixel;
	float	wallbotpixel;
	float	rayangle;

	corrdist = 0;
	distanceprojeplane = 0;
	wallstripheight = 0;
	walltoppixel = 0;
	wallbotpixel = 0;
	rayangle = 0;
	i = 0;
	rayangle = k;
	distanceprojeplane = (g_map.x / 2.0) / tan((g_fov * M_PI / 180) / 2);
	while (i < g_map.x)
	{
		rayangle = ft_raycasting(rayangle, i);
		corrdist = g_tab[i][0] * cos(rayangle - (g_rotation * M_PI / 180));
		wallstripheight = (g_tile_size / corrdist) * distanceprojeplane;
		walltoppixel = (g_map.y / 2) - (wallstripheight / 2);
		wallbotpixel = (g_map.y / 2) + (wallstripheight / 2);
		if (wallbotpixel > g_map.y)
			wallbotpixel = g_map.y;
		if (walltoppixel < 0)
			walltoppixel = 0;
		dda(i, 0, i, walltoppixel, g_ceil.color);
		ft_textures(i, walltoppixel, wallbotpixel, wallstripheight);
		dda(i, wallbotpixel, i, g_map.y, g_floor.color);
		rayangle += (g_fov * rotationangle) / g_map.x;
		i++;
	}
	return (k);
}
