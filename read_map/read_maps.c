/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:38:28 by amaach            #+#    #+#             */
/*   Updated: 2021/01/13 18:00:10 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		ft_check_param(void)
{
	if (g_map.x >= 0 && g_map.y >= 0 && g_map.we[0] != 0 && g_map.no[0] != 0
		&& g_map.so[0] != 0 && g_map.ea[0] != 0 && g_floor.a >= 0
		&& g_floor.b >= 0 && g_floor.c >= 0 && g_ceil.a >= 0
		&& g_ceil.b >= 0 && g_ceil.c >= 0)
		return (1);
	return (0);
}

void	ft_traitement(char *line, int j)
{
	int		i;

	i = 0;
	if (!line)
		return ;
	if (ft_check_param() == 0)
		ft_traitement_config(line);
	else
		ft_traitement_map(line, j);
}

void	ft_count_sprite(void)
{
	int		i;
	int		j;

	i = 0;
	while (g_la_map[i] != '\0')
	{
		j = 0;
		while (g_la_map[i][j] != '\0')
		{
			if (g_la_map[i][j] == '2')
				g_s_count++;
			j++;
		}
		i++;
	}
}

void	ft_initialisation(void)
{
	g_map.x = -1;
	g_map.y = -1;
	g_map.we = ft_strdup("");
	g_map.no = ft_strdup("");
	g_map.so = ft_strdup("");
	g_map.ea = ft_strdup("");
	g_map.s = ft_strdup("");
	g_floor.a = -1;
	g_floor.b = -1;
	g_floor.c = -1;
	g_ceil.a = -1;
	g_ceil.b = -1;
	g_ceil.c = -1;
	g_compt.c = 0;
	g_compt.f = 0;
	g_compt.no = 0;
	g_compt.ea = 0;
	g_compt.s = 0;
	g_compt.so = 0;
	g_compt.we = 0;
	g_compt.r = 0;
	g_s_count = 0;
	g_compt_d = 0;
}

void	ft_readmap(void)
{
	int		i;
	int		j;
	int		fd;
	char	*line;

	i = 0;
	j = 0;
	ft_initialisation();
	fd = open(g_map.cub, O_RDONLY);
	if (fd < 1)
		ft_error_massege("Error\nFicher non lit");
	while (1)
	{
		i = get_next_line(fd, &line);
		ft_traitement(line, i);
		free(line);
		if (i == 0)
			break ;
	}
	if (ft_check_param() == 0)
		ft_error_massege("Error\nParram non complet !");
	if (!g_la_map)
		ft_error_massege("Error\nPas de map!");
	free(g_map.cub);
}
