/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_projecting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:55:59 by amaach            #+#    #+#             */
/*   Updated: 2021/01/14 18:08:23 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		ft_tablen(char **str)
{
	int		i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

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
			color = g_textures.so[d];
		else
			color = g_textures.no[d];
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
	g_dda.compt = 1;
	dda(i, 0, i, walltop);
	while (y < wallbot)
	{
		distancefromtop = y + (wallstripheight / 2) - (g_map.y / 2);
		textureoffset_y = distancefromtop *
						((float)64 / wallstripheight);
		ft_check_texture(textureoffset_x, textureoffset_y, i, y);
		y++;
	}
}

float	ft_help_render(float ran, float distprojep, float rotan, float wallsh)
{
	float	walltoppixel;
	float	wallbotpixel;
	float	corrdist;
	int		i;

	wallbotpixel = 0;
	walltoppixel = 0;
	i = -1;
	while (++i < g_map.x)
	{
		ran = ft_raycasting(ran, i);
		corrdist = g_tab[i][0] * cos(ran - (g_rotation * M_PI / 180));
		wallsh = (g_tile_size / corrdist) * distprojep;
		walltoppixel = (g_map.y / 2) - (wallsh / 2);
		wallbotpixel = (g_map.y / 2) + (wallsh / 2);
		if (wallbotpixel > g_map.y)
			wallbotpixel = g_map.y;
		if (walltoppixel < 0)
			walltoppixel = 0;
		ft_textures(i, walltoppixel, wallbotpixel, wallsh);
		g_dda.compt = 2;
		dda(i, wallbotpixel, i, g_map.y);
		ran += (g_fov * rotan) / g_map.x;
	}
	return (ran);
}

float	renderprojectionwall(float k, float rotationangle)
{
	int		i;
	float	distanceprojeplane;
	float	wallstripheight;

	wallstripheight = 0;
	distanceprojeplane = 0;
	i = 0;
	distanceprojeplane = (g_map.x / 2.0) / tan((g_fov * M_PI / 180) / 2);
	k = ft_help_render(k, distanceprojeplane, rotationangle, wallstripheight);
	return (k);
}
