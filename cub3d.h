/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 13:46:40 by amaach            #+#    #+#             */
/*   Updated: 2021/01/04 18:51:44 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <limits.h>
# include "libft.h"

typedef struct	s_dimention {
	int		x;
	int		y;
	char	*WE;
	char	*NO;
	char	*SO;
	char	*EA;
	char	*S;
}				t_dimention;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_colors {
	int		a;
	int		b;
	int		c;
	int		color;
}				t_colors;

typedef struct	s_point {
	float	x;
	float	y;
}				t_point;

typedef struct	s_ray {
	int		FacingDown;
	int		FacingUp;
	int		FacingRight;
	int		FacingLeft;
}				t_ray;

typedef struct	s_wallhit{
	float	Horiz_X;
	float	Horiz_Y;
	float	Verti_X;
	float	Verti_Y;
	float	X;
	float	Y;
	float	distance;
	float	Angle;
}				t_wallhit;

typedef struct	s_texture{
	int		width;
	int		height;
	char	*path;
	int		*we;
	int		*ea;
	int		*no;
	int		*so;
	int		*tab;
}				t_texture;

typedef struct	s_check{
	int		r;
	int		so;
	int		we;
	int		no;
	int		ea;
	int		s;
	int		f;
	int		c;
}				t_check;

typedef struct	s_sprite{
	float	x_off;
	float	y_off;
	float	x;
	float	y;
	float	dist;
	float	size;
}				t_sprite;

t_check			g_compt;
t_wallhit		g_wallhit;
t_ray			g_ray;
t_data			g_img;
t_point			g_position;
t_point			g_player;
t_dimention		g_map;
t_colors		g_floor;
t_colors		g_ceil;
t_texture		g_textures;
t_data			g_texture;
t_sprite		*g_sprite;
char	**g_la_map;
char	*g_join;
float	g_fov;
int		g_tile_size;
int		g_turn_direction;
int		g_walk_direction;
float	g_rotation;
int		g_key_pud;
int		g_s_count;
int		g_key_pud1;
int		g_key_prl;
int		g_key_prl1;
int		g_key;
int		g_highest_ligne;
int		g_highest_colone;
int		g_check_playerdraw;
int		g_foundavertiwallhit;
int		g_foundahorizwallhit;
float	g_wallhithorizdist;
float	g_wallhitvertidist;
int		g_washitverti;
void	*g_mlx_ptr;
void	*g_win_ptr;
float	g_w_width;
float	g_w_height;
int		g_numberofrays;
float	g_tab[5028][4];

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	dda(float X0, float Y0, float X1, float Y1, unsigned int long long str);
float	cddp(float x1, float y1, float x2, float y2);
void	ft_error_massege(char *str);
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
float	ft_raycasting(float k, int i);
int		nowall(int key);
float	renderprojectionwall(float k, float rotationangle);
void	draw_sprite(int id);
void	to_sprite(void);
void	to_sort(void);
void	init_sprite(void);
#endif
