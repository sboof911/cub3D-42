/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:43:22 by amaach            #+#    #+#             */
/*   Updated: 2021/01/18 12:08:11 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
					ft_error_massege("Error\n map non fermer");
				if (j > ft_strlen(g_la_map[i - 1]))
					ft_error_massege("Error\n map non fermer");
			}
			j++;
		}
		i++;
	}
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
			ft_error_massege("Error\n map non fermer");
	}
	i = 0;
	while (g_la_map[i] != 0)
	{
		if (g_la_map[i][0] == ' ' || g_la_map[i][0] == '1')
			i++;
		else
			ft_error_massege("Error\n map non fermer");
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
			ft_error_massege("Error\n map non fermer");
	}
	j = 0;
	while (g_la_map[compt][j] != '\0')
	{
		if (g_la_map[compt][j] == ' ' || g_la_map[compt][j] == '1')
			j++;
		else
			ft_error_massege("Error\n map non fermer");
	}
}
