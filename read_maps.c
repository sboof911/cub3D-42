/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_maps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 15:38:28 by amaach            #+#    #+#             */
/*   Updated: 2020/03/13 16:46:11 by amaach           ###   ########.fr       */
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

void	ft_ERROR_MASSAGE(char *str)
{
	ft_putstr_fd(str, 1);
	exit(0);
}

int		ft_check_param(void)
{
	if (map->x && map->y && map->WE[0] != 0 && map->NO[0] != 0
		&& map->SO[0] != 0 && map->EA[0] != 0 && F->a >= 0
		&& F->b >= 0 && F->c >= 0 && C->a >= 0
		&& C->b >= 0 && C->c >= 0)
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

void	ft_traitement_resolution(char *line)
{
	int		c_w;
	char	**words;
	int		i;

	i = 0;
	c_w = ft_count_words(line, ' ');
	words = ft_split(line, ' ');
	if (c_w != 3)
		ft_ERROR_MASSAGE("ERROR : \nNombre d'argument n est pas compatible");
	if (ft_arrayisdigit(words[1]) == 1)
		map->x = ft_atoi(words[1]);
	else
		ft_ERROR_MASSAGE("ERROR : \nLa Resolution n est pas compatible");
	if (ft_arrayisdigit(words[2]) == 1)
		map->y = ft_atoi(words[2]);
	else
		ft_ERROR_MASSAGE("ERROR : \nLa Resolution n est pas compatible");
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
		if (words[0][0] == 'W' && words[0][1] == 'E')
			map->WE = ft_alloue_free(map->WE, words[1]);
		else if (words[0][0] == 'N' 
				&& words[0][1] == 'O' && words[0][2] == '\0')
			map->NO = ft_alloue_free(map->NO, words[1]);
		else if (words[0][0] == 'E' 
				&& words[0][1] == 'A' && words[0][2] == '\0')
			map->EA = ft_alloue_free(map->EA, words[1]);
		else if (words[0][0] == 'S' 
				&& words[0][1] == 'O' && words[0][2] == '\0')
			map->SO = ft_alloue_free(map->SO, words[1]);
		else
			ft_ERROR_MASSAGE("ERROR : \nSyntax ERROR");
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
		ft_ERROR_MASSAGE("ERROR : \nNombre d'argument n est pas compatible");
	if (ft_strlen(words[0]) == 2)
		ft_help_path(words);
	if (ft_strlen(words[0]) == 1 && words[0][0] == 'S')
	{
		if (ft_checkispath(words[1]) == 1)
			map->S = ft_alloue_free(map->S, words[1]);
	}
	ft_free(words, ft_tablen(words));
}

void	ft_help_2_colors(char S, int a, int b, int c)
{
	if (S == 'C')
	{
		C->a = a;
		C->b = b;
		C->c = c;
	}
	else
	{
		F->a = a;
		F->b = b;
		F->c = c;
	}
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
		ft_ERROR_MASSAGE("ERROR : \nNombre d'argument n est pas compatible");
	if ((ft_arrayisdigit(colors[0]) == 1) && (ft_arrayisdigit(colors[1]) == 1)
		&& (ft_arrayisdigit(colors[2]) == 1))
	{
		a = ft_atoi(colors[0]);
		b = ft_atoi(colors[1]);
		c = ft_atoi(colors[2]);
	}
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
		ft_ERROR_MASSAGE("ERROR : \nNombre d'argument n est pas compatible");
	if (words[0][0] == 'C' && words[0][1] == '\0')
		ft_help_colors(words, 'C');
	else if (words[0][0] == 'F' && words[0][1] == '\0')
		ft_help_colors(words, 'F');
	ft_free(words, ft_tablen(words));
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
			ft_ERROR_MASSAGE("ERROR : \n Mal carractaire mit sur la map");
	}
	i = 0;
	while (la_map[i] != 0)
	{
		if (la_map[0][i] == ' ' || la_map[0][i] == '1')
			i++;
		else
			ft_ERROR_MASSAGE("ERROR : \n Mal carractaire mit sur la map");
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
			ft_ERROR_MASSAGE("ERROR : \n Mal carractaire mit sur la map");
	}
	j = 0;
	while (la_map[compt][j] != '\0')
	{
		if (la_map[compt][j] == ' ' || la_map[compt][j] == '1')
			j++;
		else
			ft_ERROR_MASSAGE("ERROR : \n Mal carractaire mit sur la map");
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
			if (la_map[i][j] == '0')
			{
				if ((la_map[i - 1][j] == ' ') || (la_map[i + 1][j] == ' ')
					|| (la_map[i][j - 1] == ' ') || (la_map[i][j + 1] == ' '))
					ft_ERROR_MASSAGE("ERROR : \n Mal carractaire mit sur la map");
				if (j > strlen(la_map[i - 1]))
					ft_ERROR_MASSAGE("ERROR : \n Mal carractaire mit sur la map");
			}
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
}

void	ft_traitement_map(char *line, int j)
{
	char	*str;

	if (line[0] == '\0' && !join)
		return ;
	else
	{
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
			free(join);
			ft_get_error_map();
		}
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
	map->x = 0;
	map->y = 0;
	map->WE = ft_strdup("");
	map->NO = ft_strdup("");
	map->SO = ft_strdup("");
	map->EA = ft_strdup("");
	map->S = ft_strdup("");
	F->a = -1;
	F->b = -1;
	F->c = -1;
	C->a = -1;
	C->b = -1;
	C->c = -1;
}

void	ft_readmap(void)
{
	int		i;
	int		j;
	int		fd;
	char	*line;

	i = 0;
	j = 0;
	if (!(map = malloc(sizeof(t_dimention))))
		ft_ERROR_MASSAGE("ERROR : \nPas bien alloué");
	if (!(F = malloc(sizeof(t_colors))))
		ft_ERROR_MASSAGE("ERROR : \nPas bien alloué");
	if (!(C = malloc(sizeof(t_colors))))
		ft_ERROR_MASSAGE("ERROR : \nPas bien alloué");
	ft_initialisation();
	fd = open("maps.cub", O_RDONLY);
	if (fd < 1)
		ft_ERROR_MASSAGE("ERROR : \nFicher non lit");
	while (1)
	{
		i = get_next_line(fd, &line);
		ft_traitement(line, i);
		free(line);
		if (i == 0)
			break ;
	}
}

// int	main()
// {
// 	int	i=0;
// 	ft_readmap();
// 	printf("%d\n\n\n", map->x);
// 	while (la_map[i] != '\0')
// 	{
// 		printf("%s\n", la_map[i++]);
// 	}
// 	return (0);
// }
