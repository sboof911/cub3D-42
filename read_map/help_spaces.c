/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:57:13 by amaach            #+#    #+#             */
/*   Updated: 2021/01/13 17:58:45 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int				ft_arrayisdigit(char *str)
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

void			ft_regle_reso(char **words)
{
	if (words[0][0] == 'R' && words[0][1] == '\0')
	{
		if (ft_arrayisdigit(words[1]) == 1)
		{
			if (ft_strlen(words[1]) > 4)
				g_map.x = 2560;
			else
				g_map.x = ft_atoi(words[1]);
		}
		else
			ft_error_massege("Error\nLa Resolution n est pas compatible");
		if (ft_arrayisdigit(words[2]) == 1)
		{
			if (ft_strlen(words[2]) > 4)
				g_map.y = 1440;
			else
				g_map.y = ft_atoi(words[2]);
		}
		else
			ft_error_massege("Error\nLa Resolution n est pas compatible");
	}
	else
		ft_error_massege("Error\nmal carractere en resolution");
}

static void		ft_addspace3(int i, int k, int j, char **stre)
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

static int		ft_addspace2(int i, char **stre)
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

void			ft_addspace(void)
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
