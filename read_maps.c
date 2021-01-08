/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:38:28 by amaach            #+#    #+#             */
/*   Updated: 2021/01/08 17:35:01 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_tablen(char **str)
{
	int		i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

void	ft_error_massege(char *str)
{
	ft_putstr_fd(str, 1);
	exit(0);
}

int		ft_check_param(void)
{
	if (g_map.x && g_map.y && g_map.we[0] != 0 && g_map.no[0] != 0
		&& g_map.so[0] != 0 && g_map.ea[0] != 0 && g_floor.a >= 0
		&& g_floor.b >= 0 && g_floor.c >= 0 && g_ceil.a >= 0
		&& g_ceil.b >= 0 && g_ceil.c >= 0)
		return (1);
	return (0);
}

int		ft_arrayisdigit(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 1)
			i++;
		else
			return (-1);
	}
	return (1);
}

void	ft_regle_reso(void)
{
	if (g_map.x > 2560)
		g_map.x = 2560;
	if (g_map.y > 1440)
		g_map.y = 1440;
	if (g_map.x < 100 || g_map.y < 100)
		ft_error_massege("Error\nResolution super minim veuillez l augmenter");
}

void	ft_traitement_resolution(char *line)
{
	int		c_w;
	char	**words;
	int		i;

	i = 0;
	c_w = ft_count_words(line, ' ');
	words = ft_split(line, ' ');
	if (c_w != 3)
		ft_error_massege("Error\nNombre d'argument n est pas compatible");
	if (ft_arrayisdigit(words[1]) == 1)
		g_map.x = ft_atoi(words[1]);
	else
		ft_error_massege("Error\nLa Resolution n est pas compatible");
	if (ft_arrayisdigit(words[2]) == 1)
		g_map.y = ft_atoi(words[2]);
	else
		ft_error_massege("Error\nLa Resolution n est pas compatible");
	ft_regle_reso();
	g_compt.r++;
	ft_free(words, ft_tablen(words));
}

int		ft_checkispath(char *str)
{
	int		i;

	i = 0;
	i = open(str, O_RDONLY);
	if (i > 0)
		return (1);
	return (0);
}

char	*ft_alloue_free(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	free(s1);
	s1 = ft_strdup(str);
	free(str);
	return (s1);
}

void	ft_help_path(char **words)
{
	if (ft_checkispath(words[1]) == 1)
	{
		if (words[0][0] == 'W' && words[0][1] == 'E'
			&& words[0][2] == '\0' && (++g_compt.we))
			g_map.we = ft_alloue_free(g_map.we, words[1]);
		else if (words[0][0] == 'N' && words[0][1] == 'O'
				&& words[0][2] == '\0' && (++g_compt.no))
			g_map.no = ft_alloue_free(g_map.no, words[1]);
		else if (words[0][0] == 'E' && words[0][1] == 'A'
				&& words[0][2] == '\0' && (++g_compt.ea))
			g_map.ea = ft_alloue_free(g_map.ea, words[1]);
		else if (words[0][0] == 'S' && words[0][1] == 'O'
				&& words[0][2] == '\0' && (++g_compt.so))
			g_map.so = ft_alloue_free(g_map.so, words[1]);
		else if (words[0][0] == 'S' && words[0][1] == '\0'
				&& (++g_compt.s))
			g_map.s = ft_alloue_free(g_map.s, words[1]);
		else
			ft_error_massege("Error\nSyntax ERROR");
	}
}

void	ft_traitement_path(char *line)
{
	int		c_w;
	char	**words;
	int		i;

	i = 0;
	c_w = ft_count_words(line, ' ');
	words = ft_split(line, ' ');
	if (c_w != 2)
		ft_error_massege("Error\nNombre d'argument n est pas compatible");
	if (ft_strlen(words[0]) < 3)
		ft_help_path(words);
	else
		ft_error_massege("Error\nSyntax ERROR");
	ft_free(words, ft_tablen(words));
}

void	ft_help_2_colors(char s, int a, int b, int c)
{
	if (a > 255 || b > 255 || c > 255)
		ft_error_massege("Error\nCouleur est supp a 255");
	if (s == 'C')
	{
		g_compt.c++;
		g_ceil.color = a << 16 | b << 8 | c;
		g_ceil.a = a;
		g_ceil.b = b;
		g_ceil.c = c;
	}
	else
	{
		g_compt.f++;
		g_floor.color = a << 16 | b << 8 | c;
		g_floor.a = a;
		g_floor.b = b;
		g_floor.c = c;
	}
}

void	ft_check_virgule(char *words)
{
	int		i;
	int		compt;

	i = 0;
	compt = 0;
	while (words[i] != '\0')
	{
		if (words[i] == ',')
			compt++;
		i++;
	}
	if (compt > 2)
		ft_error_massege("Error\ntrop de virgule");
}

void	ft_help_colors(char **words, char s)
{
	int		a;
	int		b;
	int		c;
	int		c_w;
	char	**colors;

	a = 0;
	b = 0;
	c = 0;
	c_w = ft_count_words(words[1], ',');
	colors = ft_split(words[1], ',');
	if (c_w != 3)
		ft_error_massege("Error\n Nombre d'argument n est pas compatible");
	ft_check_virgule(words[1]);
	if (ft_arrayisdigit(colors[0]) + ft_arrayisdigit(colors[1])
		+ ft_arrayisdigit(colors[2]) == 3)
	{
		a = ft_atoi(colors[0]);
		b = ft_atoi(colors[1]);
		c = ft_atoi(colors[2]);
	}
	else
		ft_error_massege("Error\nCarractere mal mit en couleur");
	ft_free(colors, ft_tablen(colors));
	ft_help_2_colors(s, a, b, c);
}

void	ft_traitement_colors(char *line)
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

void	ft_check_double(void)
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
}

void	ft_traitement_config(char *line)
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

void	ft_error_colones(void)
{
	int		i;
	int		compt;

	i = 0;
	while (g_la_map[i] != 0)
	{
		compt = ft_strlen(g_la_map[i]) - 1;
		if (g_la_map[i][compt] == ' ' || g_la_map[i][compt] == '1')
			i++;
		else
			ft_error_massege("Error\n map non fermer au colone 1");
	}
	i = 0;
	while (g_la_map[i] != 0)
	{
		if (g_la_map[0][i] == ' ' || g_la_map[0][i] == '1')
			i++;
		else
			ft_error_massege("Error\n map non fermer au colone 2");
	}
}

void	ft_error_lignes(void)
{
	int		j;
	int		compt;

	j = 0;
	compt = ft_tablen(g_la_map) - 1;
	while (g_la_map[0][j] != '\0')
	{
		if (g_la_map[0][j] == ' ' || g_la_map[0][j] == '1')
			j++;
		else
			ft_error_massege("Error\n map non fermer en ligne 1");
	}
	j = 0;
	while (g_la_map[compt][j] != '\0')
	{
		if (g_la_map[compt][j] == ' ' || g_la_map[compt][j] == '1')
			j++;
		else
			ft_error_massege("Error\n map non fermer en ligne 2");
	}
}

void	ft_error_zero(void)
{
	int		i;
	size_t	j;

	i = 1;
	while (i < ft_tablen(g_la_map) - 1)
	{
		j = 1;
		while (j < ft_strlen(g_la_map[i]) - 1)
		{
			if (g_la_map[i][j] == '0' || g_la_map[i][j] == '2'
				|| g_la_map[i][j] == 'N' || g_la_map[i][j] == 'W'
				|| g_la_map[i][j] == 'E' || g_la_map[i][j] == 'S')
			{
				if ((g_la_map[i - 1][j] == ' ') || (g_la_map[i + 1][j] == ' ')
					|| (g_la_map[i][j - 1] == ' ')
					|| (g_la_map[i][j + 1] == ' '))
					ft_error_massege("Error\n map non fermer en ligne 3");
				if (j > strlen(g_la_map[i - 1]))
					ft_error_massege("Error\n map non fermerrr2");
			}
			j++;
		}
		i++;
	}
}

void	ft_addspace3(int i, int k, int j, char **stre)
{
	size_t	l;

	l = 0;
	while (j < g_highest_ligne + 2)
	{
		if (j == 0)
			stre[i][j] = ' ';
		else
		{
			if (g_la_map[k][l] != '\0' && l < ft_strlen(g_la_map[k]))
			{
				stre[i][j] = g_la_map[k][l];
				l++;
			}
			else
				stre[i][j] = ' ';
		}
		j++;
	}
	stre[i][j] = '\0';
}

int		ft_addspace2(int i, char **stre)
{
	int		j;
	int		l;
	int		k;

	k = -1;
	i = 0;
	while (i < g_high_colone + 2)
	{
		j = 0;
		l = 0;
		if (i == 0 || i == g_high_colone + 1)
		{
			while (j < g_highest_ligne + 2)
			{
				stre[i][j] = ' ';
				j++;
			}
			stre[i][j] = '\0';
		}
		else
			ft_addspace3(i, k, j, stre);
		k++;
		i++;
	}
	return (i);
}

void	ft_addspace(void)
{
	char	**stre;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!(stre = (char **)malloc(sizeof(char *) * ((g_high_colone + 2 + 1)))))
		ft_error_massege("Error\n Pas bien alloué");
	while (++i < g_high_colone + 2)
	{
		if (!(stre[i] = (char *)malloc(sizeof(char *) *
			((g_highest_ligne + 2 + 1)))))
			ft_error_massege("Error\n Pas bien alloué");
	}
	i = ft_addspace2(i, stre);
	stre[i] = 0;
	ft_free(g_la_map, g_high_colone);
	j = -1;
	if (!(g_la_map = (char **)malloc(sizeof(char *)
		* ((g_high_colone + 2 + 1)))))
		ft_error_massege("Error\nPas bien alloué");
	while (++j < g_high_colone + 2)
		g_la_map[j] = ft_strdup(stre[j]);
	g_la_map[j] = 0;
	ft_free(stre, g_high_colone + 2);
}

void	ft_countmap(void)
{
	int		i;
	int		l;
	int		k;

	l = 0;
	k = 0;
	i = 1;
	g_highest_ligne = 0;
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

void	ft_count_players(void)
{
	int		i;
	int		j;
	int		compt;

	compt = 0;
	i = 0;
	while (g_la_map[i] != '\0')
	{
		j = 0;
		while (g_la_map[i][j] != '\0')
		{
			if (g_la_map[i][j] == 'N' || g_la_map[i][j] == 'E'
				|| g_la_map[i][j] == 'W' || g_la_map[i][j] == 'S')
				compt++;
			j++;
		}
		i++;
	}
	if (compt > 1)
		ft_error_massege("Error\nPlusieurs joueurs sont detecter xD");
	if (compt == 0)
		ft_error_massege("Error\nposition player not found");
}

void	ft_error_map_c(void)
{
	int		i;
	int		j;

	i = 0;
	while (g_la_map[i] != '\0')
	{
		j = 0;
		while (g_la_map[i][j] != '\0')
		{
			if (g_la_map[i][j] == '1' || g_la_map[i][j] == '0'
				|| g_la_map[i][j] == '2' || g_la_map[i][j] == ' '
				|| g_la_map[i][j] == 'W' || g_la_map[i][j] == 'S'
				|| g_la_map[i][j] == 'E' || g_la_map[i][j] == 'N')
				j++;
			else
				ft_error_massege("Error\nCarraterre mal mit sur la map !!");
		}
		i++;
	}
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

void	ft_get_error_map(void)
{
	ft_error_lignes();
	ft_error_colones();
	ft_error_zero();
	ft_count_players();
	ft_error_map_c();
	ft_count_sprite();
}

void	ft_traitement_map(char *line, int j)
{
	char	*str;

	if (ft_check_param() == 0)
		ft_error_massege("Error\nun des param n est pas mit !");
	if (!g_join)
		g_join = ft_strdup("");
	if (line && j != 0)
	{
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
		ft_countmap();
		free(g_join);
		ft_get_error_map();
	}
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

void	ft_initialisation(void)
{
	g_map.x = 0;
	g_map.y = 0;
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
	free(g_map.cub);
}
