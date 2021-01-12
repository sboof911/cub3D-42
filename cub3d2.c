/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 11:38:43 by amaach            #+#    #+#             */
/*   Updated: 2021/01/11 14:34:51 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(int x, int y, int color)
{
	int		*dst;

	dst = (int *)mlx_get_data_addr(g_img.img, &g_img.bits_per_pixel,
		&g_img.line_length, &g_img.endian);
	if (x < g_map.x && y < g_map.y && x >= 0 && y >= 0)
		dst[y * (int)g_map.x + x] = color;
}

void	ft_checkdirectionplayer(int i, int j)
{
	if (g_la_map[i][j] == 'N')
		g_rotation = 270;
	else if (g_la_map[i][j] == 'S')
		g_rotation = 90;
	else if (g_la_map[i][j] == 'W')
		g_rotation = 180;
	else if (g_la_map[i][j] == 'E')
		g_rotation = 0;
}

int		abs(int n)
{
	return ((n > 0) ? n : (n * (-1)));
}

void	dda(float x0, float y0, float x1, float y1)
{
	float	x;
	float	y;
	int		i;
	int		str;

	i = 0;
	g_dda.dx = x1 - x0;
	g_dda.dy = y1 - y0;
	g_dda.steps = abs(g_dda.dx) > abs(g_dda.dy) ? abs(g_dda.dx) : abs(g_dda.dy);
	if (g_dda.compt == 1)
		str = g_ceil.color;
	if (g_dda.compt == 2)
		str = g_floor.color;
	if (g_dda.steps < 1)
		g_dda.steps = 1;
	g_dda.xinc = g_dda.dx / (float)g_dda.steps;
	g_dda.yinc = g_dda.dy / (float)g_dda.steps;
	x = x0;
	y = y0;
	while (i++ <= g_dda.steps)
	{
		my_mlx_pixel_put(x, y, str);
		x += g_dda.xinc;
		y += g_dda.yinc;
	}
}

void	draw_player(void)
{
	int		i;
	float	k;
	float	rotationangle;
	float	movespeed;
	float	rotationspeed;

	g_numberofrays = g_map.x;
	movespeed = 2;
	i = 0;
	rotationangle = M_PI / 180;
	rotationspeed = 2 * g_turn_direction;
	g_rotation += rotationspeed;
	k = (g_rotation - 30) * rotationangle;
	if (g_rotation < 0)
		g_rotation += 360;
	g_rotation = fmod(g_rotation, 360);
	if (g_player.x == 0 && g_player.y == 0)
	{
		g_player.x = g_position.x + g_tile_size / 2;
		g_player.y = g_position.y + g_tile_size / 2;
	}
	renderprojectionwall(k, rotationangle);
}

void	ft_draw_map(void)
{
	int		i;
	int		j;

	i = -1;
	while (g_la_map[++i] != '\0')
	{
		g_position.x = 0;
		j = -1;
		while (g_la_map[i][++j] != '\0')
		{
			if ((g_la_map[i][j] == 'N' || g_la_map[i][j] == 'W'
			|| g_la_map[i][j] == 'S' || g_la_map[i][j] == 'E')
			&& g_check_playerdraw == 0)
			{
				ft_checkdirectionplayer(i, j);
				draw_player();
				g_check_playerdraw++;
			}
			g_position.x = g_position.x + g_tile_size;
		}
		g_position.y = g_position.y + g_tile_size;
	}
	if (g_check_playerdraw == 0)
		ft_error_massege("Error\nposition player not found");
}

int		nowallx(int key)
{
	int	i;
	int	j;
	int	s;
	int	x;
	int	y;

	if (key == -1)
		s = -20;
	if (key == 1)
		s = 20;
	x = g_player.x + (s * cos(g_rotation * (M_PI / 180)));
	y = g_player.y;
	i = y / g_tile_size;
	j = x / g_tile_size;
	i = i < 0 ? 0 : i;
	j = j < 0 ? 0 : j;
	i = i > g_high_colone ? g_high_colone : i;
	j = j > g_highest_ligne ? g_highest_ligne : j;
	if (g_la_map[i][j] == '1' || g_la_map[i][j] == ' ' || g_la_map[i][j] == '2')
		return (0);
	return (1);
}

int		nowally(int key)
{
	int	i;
	int	j;
	int	s;
	int	x;
	int	y;

	s = 0;
	if (key == -1)
		s = -20;
	if (key == 1)
		s = 20;
	x = g_player.x;
	y = g_player.y + (s * sin(g_rotation * (M_PI / 180)));
	i = y / g_tile_size;
	j = x / g_tile_size;
	i = i < 0 ? 0 : i;
	j = j < 0 ? 0 : j;
	i = i > g_high_colone ? g_high_colone : i;
	j = j > g_highest_ligne ? g_highest_ligne : j;
	if (g_la_map[i][j] == '1' || g_la_map[i][j] == ' ' || g_la_map[i][j] == '2')
		return (0);
	return (1);
}

int		key_released(int key)
{
	if (key == 123 || key == 124 || key == 0 || key == 2)
		g_turn_direction = 0;
	if (key == 1 || key == 13)
		g_walk_direction = 0;
	return (0);
}

void	ft_draw_player(void)
{
	if (g_walk_direction == -1 || g_walk_direction == 1)
	{
		if (nowallx(g_walk_direction) == 1)
			g_player.x += 8 * g_walk_direction *
			cos(g_rotation * (M_PI / 180));
		if (nowally(g_walk_direction) == 1)
			g_player.y += 8 * g_walk_direction *
			sin(g_rotation * (M_PI / 180));
	}
	draw_player();
	if (g_key == 1)
		exit(0);
}

int		key_pressed(int key)
{
	if (key == 123 || key == 124 || key == 0 || key == 2)
	{
		g_key_prl1 = 1;
		if (key == 123 || key == 0)
			g_turn_direction = -1;
		if (key == 124 || key == 2)
			g_turn_direction = 1;
	}
	if (key == 1 || key == 13)
	{
		if (key == 1)
			g_walk_direction = -1;
		if (key == 13)
			g_walk_direction = 1;
	}
	if (key == 53)
		g_key = 1;
	return (0);
}

int		direction_player(void)
{
	mlx_destroy_image(g_mlx_ptr, g_img.img);
	g_img.img = mlx_new_image(g_mlx_ptr, g_map.x, g_map.y);
	ft_draw_map();
	ft_draw_player();
	to_sprite();
	mlx_put_image_to_window(g_mlx_ptr, g_win_ptr, g_img.img, 0, 0);
	if (g_map.save == 1)
	{
		save_bmp();
		exit(0);
	}
	return (0);
}

void	initialisation(void)
{
	g_fov = 60;
	g_key = 0;
	g_key_prl1 = 0;
	g_tile_size = 64;
	g_check_playerdraw = 0;
	g_player.x = 0;
	g_player.y = 0;
	g_position.x = 0;
	g_position.y = 0;
	g_walk_direction = 0;
	g_turn_direction = 0;
	g_map.save = 0;
}

void	ft_free_textures(void)
{
	free(g_map.we);
	free(g_map.so);
	free(g_map.no);
	free(g_map.ea);
}

void	ft_initia_texture(void)
{
	g_we.img = mlx_xpm_file_to_image(g_mlx_ptr, g_map.we,
					&g_we.width, &g_we.height);
	if (g_we.img == 0)
		ft_error_massege("Texture west est vide !!");
	g_textures.we = (int *)mlx_get_data_addr(g_we.img,
		&g_we.bits_per_pixel, &g_we.line_length, &g_we.endian);
	g_so.img = mlx_xpm_file_to_image(g_mlx_ptr, g_map.so,
					&g_so.width, &g_so.height);
	if (g_so.img == 0)
		ft_error_massege("Texture south est vide !!");
	g_textures.so = (int *)mlx_get_data_addr(g_so.img,
		&g_so.bits_per_pixel, &g_so.line_length, &g_so.endian);
	g_no.img = mlx_xpm_file_to_image(g_mlx_ptr, g_map.no,
					&g_no.width, &g_no.height);
	if (g_no.img == 0)
		ft_error_massege("Texture north est vide !!");
	g_textures.no = (int *)mlx_get_data_addr(g_no.img,
		&g_no.bits_per_pixel, &g_no.line_length, &g_no.endian);
	g_ea.img = mlx_xpm_file_to_image(g_mlx_ptr, g_map.ea,
					&g_ea.width, &g_ea.height);
	if (g_ea.img == 0)
		ft_error_massege("Texture east est vide !!");
	g_textures.ea = (int *)mlx_get_data_addr(g_ea.img,
		&g_ea.bits_per_pixel, &g_ea.line_length, &g_ea.endian);
	ft_free_textures();
}

int		ft_exit_x(void)
{
	exit(0);
}

void	ft_gere_arg(int argc, char **argv)
{
	char	*str;
	int		i;

	i = 0;
	if (argc < 2 || argc > 3)
		ft_error_massege("Error\nNombre d'argument non compatible");
	str = ft_strrev(argv[1]);
	if (str[0] == 'b' && str[1] == 'u' && str[2] == 'c' && str[3] == '.')
		g_map.cub = ft_strdup(ft_strrev(argv[1]));
	else
		ft_error_massege("Error\nL extension .cub est mal mit");
	if (argc == 3)
	{
		if (argv[2][0] == '-' && argv[2][1] == '-' && argv[2][2] == 's'
			&& argv[2][3] == 'a' && argv[2][4] == 'v'
			&& argv[2][5] == 'e' && argv[2][6] == '\0')
			g_map.save = 1;
		else
			ft_error_massege("Error\nArgument save pas bien ecrit");
	}
}

int		main(int argc, char **argv)
{
	initialisation();
	ft_gere_arg(argc, argv);
	ft_readmap();
	g_mlx_ptr = mlx_init();
	g_win_ptr = mlx_new_window(g_mlx_ptr, g_map.x, g_map.y, "sboof");
	g_img.img = mlx_new_image(g_mlx_ptr, g_map.x, g_map.y);
	g_img.addr = mlx_get_data_addr(g_img.img, &g_img.bits_per_pixel,
				&g_img.line_length, &g_img.endian);
	ft_initia_texture();
	mlx_hook(g_win_ptr, 2, 0, key_pressed, (void *)0);
	mlx_hook(g_win_ptr, 3, 0, key_released, (void *)0);
	mlx_hook(g_win_ptr, 17, 0, ft_exit_x, (void *)0);
	init_sprite();
	mlx_loop_hook(g_mlx_ptr, direction_player, (void *)0);
	mlx_loop(g_mlx_ptr);
	system("leaks checker");
}
