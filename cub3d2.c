/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 11:38:43 by amaach            #+#    #+#             */
/*   Updated: 2021/01/04 18:05:46 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	int		*dst;

	dst = (int *)mlx_get_data_addr(img.img, &img.bits_per_pixel,
		&img.line_length, &img.endian);
	if (x < map.x && y < map.y && x >= 0 && y >= 0)
		dst[y * (int)map.x + x] = color;
}

void	draw_tile(void)
{
	float i;
	float j;

	i = position.x;
	j = position.y;
	while (i <= position.x + TILE_SIZE)
	{
		j = position.y;
		while (j <= position.y + TILE_SIZE)
			j++;
		i++;
	}
}

void	ft_checkdirectionplayer(int i, int j)
{
	if (la_map[i][j] == 'N')
		rotation = 270;
	else if (la_map[i][j] == 'S')
		rotation = 90;
	else if (la_map[i][j] == 'W')
		rotation = 180;
	else if (la_map[i][j] == 'E')
		rotation = 0;
}

int		abs(int n)
{
	return ((n > 0) ? n : (n * (-1)));
}

void	dda(float X0, float Y0, float X1, float Y1, unsigned int long long str)
{
    int		dx;
    int		dy;
    int		steps;
    float	Xinc;
    float	Yinc;
    float	X;
    float	Y;
	int		i;

	i = 0;
	dx = X1 - X0;
	dy = Y1 - Y0;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	Xinc = dx / (float) steps;
	Yinc = dy / (float) steps;
	X = X0;
	Y = Y0;
    while (i++ <= steps)
    {
      	my_mlx_pixel_put(&img, X, Y, str);
        X += Xinc;
        Y += Yinc;
    }
}

void	draw_player(void)
{
	int		i;
	float	k;
	float	rotationangle;
	float	movespeed;
	float	rotationspeed;

	g_numberofrays = map.x;
	movespeed = 2;
	i = 0;
	rotationangle = M_PI / 180;
	rotationspeed = 2 * turn_direction;
	rotation += rotationspeed;
	k = (rotation - 30) * rotationangle;
	if (rotation < 0)
		rotation += 360;
	rotation = fmod(rotation, 360);
	if (player.x == 0 && player.y == 0)
	{
		player.x = position.x + TILE_SIZE / 2;
		player.y = position.y + TILE_SIZE / 2;
	}
	renderprojectionwall(k, rotationangle);
}

void	ft_draw_map(void)
{
	int		i;
	int		j;

	i = 0;
	while (la_map[i] != '\0')
	{
		position.x = 0;
		j = 0;
		while (la_map[i][j] != '\0')
		{
			if (la_map[i][j] == '1')
				draw_tile();
			if ((la_map[i][j] == 'N' || la_map[i][j] == 'W'
		|| la_map[i][j] == 'S' || la_map[i][j] == 'E') && check_playerdraw == 0)
			{
				ft_checkdirectionplayer(i, j);
				draw_player();
				check_playerdraw++;
			}
			position.x = position.x + TILE_SIZE;
			j++;
		}
		position.y = position.y + TILE_SIZE;
		i++;
	}
	if (check_playerdraw == 0)
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
	x = player.x + (s * cos(rotation * (M_PI / 180)));
	y = player.y;
	i = y / TILE_SIZE;
	j = x / TILE_SIZE;
	if (la_map[i][j] == '1' || la_map[i][j] == ' ' || la_map[i][j] == '2')
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

	if (key == -1)
		s = -20;
	if (key == 1)
		s = 20;
	x = player.x;
	y = player.y + (s * sin(rotation * (M_PI / 180)));
	i = y / TILE_SIZE;
	j = x / TILE_SIZE;
	if (la_map[i][j] == '1' || la_map[i][j] == ' ' || la_map[i][j] == '2')
		return (0);
	return (1);
}

int		key_released(int key)
{
	if (key == 123 || key == 124 || key == 2 || key == 0)
		turn_direction = 0;
	if (key == 1 || key == 13)
		walk_direction = 0;
	return (0);
}

void	ft_draw_player(void)
{
	if (walk_direction == -1 || walk_direction == 1)
	{
		if (nowallx(walk_direction) == 1)
			player.x += 8 * walk_direction * cos(rotation * (M_PI / 180));
		if (nowally(walk_direction) == 1)
			player.y += 8 * walk_direction * sin(rotation * (M_PI / 180));
	}
	draw_player();
	if (KEY == 1)
		exit(0);
}

int		key_pressed(int key)
{
	if (key == 123 || key == 0 || key == 124 || key == 2)
	{
		KEY_PRL1 = 1;
		if (key == 123 || key == 0)
			turn_direction = -1;
		if (key == 124 || key == 2)
			turn_direction = 1;
	}
	if (key == 1 || key == 13)
	{
		KEY_PUD1 = 1;
		if (key == 1)
			walk_direction = -1;
		if (key == 13)
			walk_direction = 1;
	}
	if (key == 53)
		KEY = 1;
	return (0);
}

int		direction_player(void)
{
	mlx_destroy_image(g_mlx_ptr, img.img);
	img.img = mlx_new_image(g_mlx_ptr, map.x, map.y);
	ft_draw_map();
	ft_draw_player();
	to_sprite();
	mlx_put_image_to_window(g_mlx_ptr, g_win_ptr, img.img, 0, 0);
	return (0);
}

void	initialisation(void)
{
	FOV = 60;
	KEY = 0;
	KEY_PRL1 = 0;
	KEY_PUD1 = 0;
	TILE_SIZE = 64;
	check_playerdraw = 0;
	player.x = 0;
	player.y = 0;
	position.x = 0;
	position.y = 0;
	walk_direction = 0;
	turn_direction = 0;
}

void	ft_initia_texture(void)
{
	texture.img = mlx_xpm_file_to_image(g_mlx_ptr, map.WE,
					&textures.width, &textures.height);
	if (texture.img == NULL)
		ft_error_massege("Texture west est vide !!");
	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel,
					&texture.line_length, &texture.endian);
	textures.we = (int *)texture.addr;
	texture.img = mlx_xpm_file_to_image(g_mlx_ptr, map.SO,
					&textures.width, &textures.height);
	if (texture.img == NULL)
		ft_error_massege("Texture south est vide !!");
	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel,
					&texture.line_length, &texture.endian);
	textures.so = (int *)texture.addr;
	texture.img = mlx_xpm_file_to_image(g_mlx_ptr, map.NO, &textures.width,
					&textures.height);
	if (texture.img == NULL)
		ft_error_massege("Texture north est vide !!");
	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel,
					&texture.line_length, &texture.endian);
	textures.no = (int *)texture.addr;
	texture.img = mlx_xpm_file_to_image(g_mlx_ptr, map.EA, &textures.width,
					&textures.height);
	if (texture.img == NULL)
		ft_error_massege("Texture east est vide !!");
	texture.addr = mlx_get_data_addr(texture.img, &texture.bits_per_pixel,
					&texture.line_length, &texture.endian);
	textures.ea = (int *)texture.addr;
}

int		ft_exit_x(void)
{
	exit(0);
}

int		main(void)
{
	initialisation();
	ft_readmap();
	g_mlx_ptr = mlx_init();
	g_win_ptr = mlx_new_window(g_mlx_ptr, map.x, map.y, "sboof");
	img.img = mlx_new_image(g_mlx_ptr, map.x, map.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
				&img.line_length, &img.endian);
	ft_initia_texture();
	mlx_hook(g_win_ptr, 2, 0, key_pressed, (void *)0);
	mlx_hook(g_win_ptr, 3, 0, key_released, (void *)0);
	mlx_hook(g_win_ptr, 17, 0, ft_exit_x, (void *)0);
	init_sprite();
	mlx_loop_hook(g_mlx_ptr, direction_player, (void *)0);
	mlx_loop(g_mlx_ptr);
}
