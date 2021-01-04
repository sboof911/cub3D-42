/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:38:28 by amaach            #+#    #+#             */
/*   Updated: 2021/01/04 14:59:16 by amaach           ###   ########.fr       */
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
	if (map.x && map.y && map.WE[0] != 0 && map.NO[0] != 0
		&& map.SO[0] != 0 && map.EA[0] != 0 && F.a >= 0
		&& F.b >= 0 && F.c >= 0 && C.a >= 0
		&& C.b >= 0 && C.c >= 0)
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
	if (map.x > 2560)
		map.x = 2560;
	if (map.y > 1440)
		map.y = 1440;
	if (map.x < 100 || map.y < 100)
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
		map.x = ft_atoi(words[1]);
	else
		ft_error_massege("Error\nLa Resolution n est pas compatible");
	if (ft_arrayisdigit(words[2]) == 1)
		map.y = ft_atoi(words[2]);
	else
		ft_error_massege("Error\nLa Resolution n est pas compatible");
	ft_regle_reso();
	compt.r++;
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
			&& words[0][2] == '\0' && (++compt.we))
			map.WE = ft_alloue_free(map.WE, words[1]);
		else if (words[0][0] == 'N' && words[0][1] == 'O'
				&& words[0][2] == '\0' && (++compt.no))
			map.NO = ft_alloue_free(map.NO, words[1]);
		else if (words[0][0] == 'E' && words[0][1] == 'A'
				&& words[0][2] == '\0' && (++compt.ea))
			map.EA = ft_alloue_free(map.EA, words[1]);
		else if (words[0][0] == 'S' && words[0][1] == 'O'
				&& words[0][2] == '\0' && (++compt.so))
			map.SO = ft_alloue_free(map.SO, words[1]);
		else if (words[0][0] == 'S' && words[0][1] == '\0'
				&& (++compt.s))
			map.S = ft_alloue_free(map.S, words[1]);
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

void	ft_help_2_colors(char S, int a, int b, int c)
{
	if (a > 255 || b > 255 || c > 255)
		ft_error_massege("Error\nCouleur est supperieur a 255 svp de la regler");
	if (S == 'C')
	{
		compt.c++;
		C.color = a << 16 | b << 8 | c;
		C.a = a;
		C.b = b;
		C.c = c;
	}
	else
	{
		compt.f++;
		F.color = a << 16 | b << 8 | c;
		F.a = a;
		F.b = b;
		F.c = c;
	}
	
}

void	ft_check_virgule(char *words)
{
	int		i;
	int		compt;

	i = 0;
	compt = 0;
	while(words[i] != '\0')
	{
		if (words[i] == ',')
			compt++;
		i++;
	}
	if (compt > 2)
		ft_error_massege("Error\ntrop de virgule");
}

void	ft_help_colors(char **words, char S)
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
	ft_help_2_colors(S, a, b, c);
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
	if (compt.r > 1)
		ft_error_massege("Error\nplus d une resolution");
	if (compt.no > 1)
		ft_error_massege("Error\nplus d un path NO");
	if (compt.so > 1)
		ft_error_massege("Error\nplus d un path SO");
	if (compt.we > 1)
		ft_error_massege("Error\nplus d un path WE");
	if (compt.ea > 1)
		ft_error_massege("Error\nplus d un path EA");
	if (compt.s > 1)
		ft_error_massege("Error\nplus d un path S");
	if (compt.f > 1)
		ft_error_massege("Error\nplus d une couleur F");
	if (compt.c > 1)
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
	while (la_map[i] != 0)
	{
		compt = ft_strlen(la_map[i]) - 1;
		if (la_map[i][compt] == ' ' || la_map[i][compt] == '1')
			i++;
		else
			ft_error_massege("Error\n map non fermer au colone 1");
	}
	i = 0;
	while (la_map[i] != 0)
	{
		if (la_map[0][i] == ' ' || la_map[0][i] == '1')
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
	compt = ft_tablen(la_map) - 1;
	while (la_map[0][j] != '\0')
	{
		if (la_map[0][j] == ' ' || la_map[0][j] == '1')
			j++;
		else
			ft_error_massege("Error\n map non fermer en ligne 1");
	}
	j = 0;
	while (la_map[compt][j] != '\0')
	{
		if (la_map[compt][j] == ' ' || la_map[compt][j] == '1')
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
	while (i < ft_tablen(la_map) - 1)
	{
		j = 1;
		while (j < ft_strlen(la_map[i]) - 1)
		{
			if (la_map[i][j] == '0' || la_map[i][j] == '2' || la_map[i][j] == 'N'
				|| la_map[i][j] == 'W' || la_map[i][j] == 'E' || la_map[i][j] == 'S')
			{
				if ((la_map[i - 1][j] == ' ') || (la_map[i + 1][j] == ' ')
					|| (la_map[i][j - 1] == ' ') || (la_map[i][j + 1] == ' '))
					ft_error_massege("Error\n map non fermer en ligne 3");
				if (j > strlen(la_map[i - 1]))
					ft_error_massege("Error\n map non fermerrr2");
			}
			j++;
		}
		i++;
	}
}

void	ft_addspace3(int i, int k, int j, char **stre)
{
	int		l;

	l = 0;
	while (j < highest_ligne + 2)
	{
		if (j == 0)
			stre[i][j] = ' ';
		else
		{
			if (la_map[k][l] != '\0' && l < ft_strlen(la_map[k]))
			{
				stre[i][j] = la_map[k][l];
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
	while (i < highest_colone + 2)
	{
		j = 0;
		l = 0;
		if (i == 0 || i == highest_colone + 1)
		{
			while (j < highest_ligne + 2)
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

	i = 0;
	j = 0;
	if (!(stre = (char **)malloc(sizeof(char *) * ((highest_colone + 2 + 1)))))
		ft_error_massege("Error\n Pas bien alloué");
	while (i < highest_colone + 2)
	{
		if (!(stre[i] = (char *)malloc(sizeof(char *) * ((highest_ligne + 2 + 1)))))
			ft_error_massege("Error\n Pas bien alloué");
		i++;
	}
	i = ft_addspace2(i, stre);
	stre[i] = 0;
	ft_free(la_map, highest_colone);
	j = -1;
	if (!(la_map = (char **)malloc(sizeof(char *) * ((highest_colone + 2 + 1)))))
		ft_error_massege("Error\nPas bien alloué");
	while (++j < highest_colone + 2)
		la_map[j] = ft_strdup(stre[j]);
	la_map[j] = 0;
	ft_free(stre, highest_colone);
}

void	ft_countmap(void)
{
	int		i;
	int		l;
	int		k;

	l = 0;
	k = 0;
	i = 1;
	highest_ligne = 0;
	while (la_map[i] != '\0')
	{
		l = ft_strlen(la_map[i]);
		if (highest_ligne < l)
			highest_ligne = l;
		i++;
	}
	highest_colone = ft_tablen(la_map);
	WINDOW_HIGHT = highest_ligne * TILE_SIZE;
	WINDOW_WIDTH = highest_colone * TILE_SIZE;
	ft_addspace();
}

void	ft_count_players()
{
	int		i;
	int		j;
	int		compt;

	compt = 0;
	i = 0;
	while (la_map[i] != '\0')
	{
		j = 0;
		while (la_map[i][j] != '\0')
		{
			if (la_map[i][j] == 'N' || la_map[i][j] == 'E'
				|| la_map[i][j] == 'W' || la_map[i][j] == 'S')
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
	while (la_map[i] != '\0')
	{
		j = 0;
		while (la_map[i][j] != '\0')
		{
			if (la_map[i][j] == '1' || la_map[i][j] == '0' || la_map[i][j] == '2' || la_map[i][j] == ' '
				|| la_map[i][j] == 'W' || la_map[i][j] == 'S' || la_map[i][j] == 'E' || la_map[i][j] == 'N')
				j++;
			else
				ft_error_massege("Error\nCarraterre mal mit sur la map !!");
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
}

void	ft_traitement_map(char *line, int j)
{
	char	*str;

	if (ft_check_param() == 0)
		ft_error_massege("Error\nun des param n est pas mit !");
	if (!join)
		join = ft_strdup("");
	if (line && j != 0)
	{
		str = ft_strjoin(join, line);
		free(join);
		join = ft_strjoin(str, "\n");
		free(str);
	}
	if (j == 0 && join)
	{
		str = ft_strjoin(join, line);
		free(join);
		join = ft_strjoin(str, "\n");
		free(str);
		la_map = ft_split(join, '\n');
		ft_countmap();
		free(join);
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
	map.x = 0;
	map.y = 0;
	map.WE = ft_strdup("");
	map.NO = ft_strdup("");
	map.SO = ft_strdup("");
	map.EA = ft_strdup("");
	map.S = ft_strdup("");
	F.a = -1;
	F.b = -1;
	F.c = -1;
	C.a = -1;
	C.b = -1;
	C.c = -1;
	compt.c = 0;
	compt.f = 0;
	compt.no = 0;
	compt.ea = 0;
	compt.s = 0;
	compt.so = 0;
	compt.we = 0;
	compt.r = 0;
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
	fd = open("maps.cub", O_RDONLY);
	if (fd < 1)
		ft_error_massege("Error\nFicher non lit");
	while (1)
	{
		i = get_next_line(fd, &line);
		ft_traitement(line, i);
		free(line);
		if (i == 0)
			break;
	}
}

// int main()
// {
// 	ft_readmap();
// 	return (0);
// }