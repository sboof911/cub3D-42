/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:07:07 by amaach            #+#    #+#             */
/*   Updated: 2021/01/14 16:48:19 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			ft_error_massege(char *str)
{
	ft_putstr_fd(str, 1);
	exit(0);
}

static void		ft_countmap(char *line)
{
	int		i;
	int		l;
	int		k;

	l = 0;
	k = 0;
	i = 1;
	g_highest_ligne = 0;
	if (line[0] == '\0')
		ft_error_massege("Error\nMap finit par une ligne vide");
	while (g_la_map[i] != '\0')
	{
		l = ft_strlen(g_la_map[i]);
		if (g_highest_ligne < l)
			g_highest_ligne = l;
		i++;
	}
	g_high_colone = ft_tablen(g_la_map);
	g_w_height = g_highest_ligne * g_tile_size;
	g_w_width = g_high_colone * g_tile_size;
	ft_addspace();
}

static void		ft_get_error_map(void)
{
	ft_error_lignes();
	ft_error_colones();
	ft_error_zero();
	ft_count_players();
	ft_error_map_c();
	ft_count_sprite();
}

static void		ft_error_separation(char *line)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '1')
			g_compt_d++;
		i++;
	}
	if (g_compt_d > 0 && line[0] == '\0')
		ft_error_massege("Error\nmap separer");
}

void			ft_traitement_map(char *line, int j)
{
	char	*str;

	if (ft_check_param() == 0)
		ft_error_massege("Error\nun des param n est pas mit !");
	if (!g_join)
		g_join = ft_strdup("");
	if (line && j != 0)
	{
		ft_error_separation(line);
		str = ft_strjoin(g_join, line);
		free(g_join);
		g_join = ft_strjoin(str, "\n");
		free(str);
	}
	if (j == 0 && g_join)
	{
		str = ft_strjoin(g_join, line);
		free(g_join);
		g_join = ft_strjoin(str, "\n");
		free(str);
		g_la_map = ft_split(g_join, '\n');
		ft_countmap(line);
		free(g_join);
		ft_get_error_map();
	}
}
