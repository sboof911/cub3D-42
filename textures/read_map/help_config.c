/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:19:33 by amaach            #+#    #+#             */
/*   Updated: 2021/01/13 17:38:55 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int		ft_check_double(void)
{
	if (g_compt.r > 1)
		ft_error_massege("Error\nplus d une resolution");
	if (g_compt.no > 1)
		ft_error_massege("Error\nplus d un path NO");
	if (g_compt.so > 1)
		ft_error_massege("Error\nplus d un path SO");
	if (g_compt.we > 1)
		ft_error_massege("Error\nplus d un path WE");
	if (g_compt.ea > 1)
		ft_error_massege("Error\nplus d un path EA");
	if (g_compt.s > 1)
		ft_error_massege("Error\nplus d un path S");
	if (g_compt.f > 1)
		ft_error_massege("Error\nplus d une couleur F");
	if (g_compt.c > 1)
		ft_error_massege("Error\nplus d une couleur C");
	return (1);
}

static void		ft_traitement_colors(char *line)
{
	int		c_w;
	char	**words;
	int		i;

	i = 0;
	c_w = ft_count_words(line, ' ');
	words = ft_split(line, ' ');
	if (c_w != 2)
		ft_error_massege("Error\n Nombre d'argument n est pas compatible");
	if (words[0][0] == 'C' && words[0][1] == '\0')
		ft_help_colors(words, 'C');
	else if (words[0][0] == 'F' && words[0][1] == '\0')
		ft_help_colors(words, 'F');
	else if (words[0][1])
		ft_error_massege("Error\nparam couleur pas bien ecrit");
	ft_free(words, ft_tablen(words));
}

static void		ft_traitement_resolution(char *line)
{
	int		c_w;
	char	**words;
	int		i;

	i = 0;
	c_w = ft_count_words(line, ' ');
	words = ft_split(line, ' ');
	if (c_w != 3)
		ft_error_massege("Error\nNombre d'argument n est pas compatible");
	ft_regle_reso(words);
	if (g_map.x > 2560)
		g_map.x = 2560;
	if (g_map.y > 1440)
		g_map.y = 1440;
	g_compt.r++;
	ft_free(words, ft_tablen(words));
}

static void		ft_traitement_path(char *line)
{
	if (line[0] == 'W' && line[1] == 'E' && line[2] == ' '
		&& (++g_compt.we))
		g_map.we = ft_alloue_free(g_map.we, ft_help_path(line, 1));
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' '
		&& (++g_compt.no))
		g_map.no = ft_alloue_free(g_map.no, ft_help_path(line, 1));
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' '
		&& (++g_compt.ea))
		g_map.ea = ft_alloue_free(g_map.ea, ft_help_path(line, 1));
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' '
		&& (++g_compt.so))
		g_map.so = ft_alloue_free(g_map.so, ft_help_path(line, 1));
	else if (line[0] == 'S' && line[1] == ' ')
		g_map.s = ft_alloue_free(g_map.s, ft_help_path(line, 0));
	else
		ft_error_massege("Error\nQuelque chose ne vas pas avec les param");
}

void			ft_traitement_config(char *line)
{
	int		i;

	i = 0;
	if (line[i] == 'R')
		ft_traitement_resolution(line);
	else if (line[i] == 'W' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'S')
		ft_traitement_path(line);
	else if (line[i] == 'F' || line[i] == 'C')
		ft_traitement_colors(line);
	else if (line[i] != '\0')
		ft_error_massege("Error\nquelque chose ne vas pas au ficher!!");
	ft_check_double();
}
