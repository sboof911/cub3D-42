/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 16:09:02 by amaach            #+#    #+#             */
/*   Updated: 2021/01/13 18:48:40 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
