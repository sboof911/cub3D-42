/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_paco.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:48:54 by amaach            #+#    #+#             */
/*   Updated: 2021/01/13 17:52:01 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		ft_help_2_colors(char s, int a, int b, int c)
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

static void		ft_check_virgule(char *words)
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

void			ft_help_colors(char **words, char s)
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
		ft_error_massege("Error\n Nombre d'arg n est pas compat en couleur");
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

static int		ft_checkispath(char *str)
{
	int		i;

	i = 0;
	i = open(str, O_RDONLY);
	if (i > 0)
		return (1);
	return (0);
}

char			*ft_help_path(char *line, int j)
{
	char	*words;

	if (j == 1)
		words = line + 3;
	else
		words = line + 2;
	if (ft_checkispath(words) == 0)
		ft_error_massege("Error\nPath incorrect");
	return (words);
}
