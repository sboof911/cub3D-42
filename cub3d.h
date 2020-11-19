/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 13:46:40 by amaach            #+#    #+#             */
/*   Updated: 2020/11/18 16:54:37 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "libft.h"

typedef struct s_dimention {
	int		x;
	int 	y;
	char	*WE;
	char	*NO;
	char	*SO;
	char	*EA;
	char	*S;
}	t_dimention;

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct s_colors {
	int		a;
	int		b;
	int		c;
}	t_colors;

typedef struct maps {

	void	*windows; 
	void	*init;
}	t_maps;

typedef struct point {
	float x;
	float y;
}	t_point;

t_data  		img;
t_point			*position;
t_point			*player;
t_maps			*okey;
t_dimention		*map;
t_colors		*F;
t_colors		*C;
char	**la_map;
char	*join;
int		turn_direction;
int		walk_direction;
int		view_direction_NS;
int		view_direction_WE;
int		rotation;
int		KEY_PUD;
int		KEY_PUD1;
int		KEY_PRL;
int		KEY_PRL1;
int		KEY;
int		highest_ligne;
int		highest_colone;
int		check_playerdraw;

void	ft_ERROR_MASSAGE(char *str);
int		ft_check_param(void);
int		ft_arrayisdigit(char *str);
void	ft_traitement_resolution(char *line);
int		ft_checkispath(char *str);
char	*ft_alloue_free(char *s1, char *s2);
void	ft_help_path(char **words);
void	ft_traitement_path(char *line);
void	ft_help_2_colors(char S, int a, int b, int c);
void	ft_help_colors(char **words, char S);
void	ft_traitement_colors(char *line);
void	ft_traitement_config(char *line);
int		ft_tablen(char **str);
void	ft_error_colones(void);
void	ft_error_lignes(void);
void	ft_error_zero(void);
void	ft_get_error_map(void);
void	ft_traitement_map(char *line, int j);
void	ft_traitement(char *line, int j);
void	ft_initialisation(void);
void	ft_readmap(void);

#endif
