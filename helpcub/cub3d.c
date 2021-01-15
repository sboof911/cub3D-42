/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 11:38:43 by amaach            #+#    #+#             */
/*   Updated: 2021/01/15 09:44:35 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_alloue_free(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	free(s1);
	s1 = ft_strdup(str);
	free(str);
	return (s1);
}

void	ft_checkdirectionplayer(int i, int j)
{
	if (g_la_map[i][j] == 'N')
		g_rotation = 270;
	else if (g_la_map[i][j] == 'S')
		g_rotation = 90;
	else if (g_la_map[i][j] == 'W')
		g_rotation = 180;
	else if (g_la_map[i][j] == 'E')
		g_rotation = 0;
}

int		nowallx(int key)
{
	int	i;
	int	j;
	int	s;
	int	x;
	int	y;

	if (key == -1)
		s = -20;
	if (key == 1)
		s = 20;
	x = g_player.x + (s * cos((g_rotation + g_sidewalk) * (M_PI / 180)));
	y = g_player.y;
	i = y / g_tile_size;
	j = x / g_tile_size;
	i = i < 0 ? 0 : i;
	j = j < 0 ? 0 : j;
	i = i > g_high_colone ? g_high_colone : i;
	j = j > g_highest_ligne ? g_highest_ligne : j;
	if (g_la_map[i][j] == '1' || g_la_map[i][j] == ' ' || g_la_map[i][j] == '2')
		return (0);
	return (1);
}

int		nowally(int key)
{
	int	i;
	int	j;
	int	s;
	int	x;
	int	y;

	s = 0;
	if (key == -1)
		s = -20;
	if (key == 1)
		s = 20;
	x = g_player.x;
	y = g_player.y + (s * sin((g_rotation + g_sidewalk) * (M_PI / 180)));
	i = y / g_tile_size;
	j = x / g_tile_size;
	i = i < 0 ? 0 : i;
	j = j < 0 ? 0 : j;
	i = i > g_high_colone ? g_high_colone : i;
	j = j > g_highest_ligne ? g_highest_ligne : j;
	if (g_la_map[i][j] == '1' || g_la_map[i][j] == ' ' || g_la_map[i][j] == '2')
		return (0);
	return (1);
}

void	ft_draw_player(void)
{
	if (g_walk_direction == -1 || g_walk_direction == 1)
	{
		if (nowallx(g_walk_direction) == 1)
			g_player.x += 8 * g_walk_direction *
			cos((g_rotation + g_sidewalk) * (M_PI / 180));
		if (nowally(g_walk_direction) == 1)
			g_player.y += 8 * g_walk_direction *
			sin((g_rotation + g_sidewalk) * (M_PI / 180));
	}
	draw_player();
	if (g_key == 1)
		exit(0);
}
