/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 11:38:43 by amaach            #+#    #+#             */
/*   Updated: 2020/12/08 17:17:23 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
int	*add;

	add = (int *)mlx_get_data_addr(t_mlx.img.img, &t_mlx.img.bits_per_pixel,
			&t_mlx.img.line_length, &t_mlx.img.endian);
	if (x < t_mlx.resul.width && y < t_mlx.resul.height && x >= 0 && y >= 0)
		add[y * (int)t_mlx.resul.width + x] = color;
*/

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    int		*dst;

	dst = (int *)mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
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
		{
			my_mlx_pixel_put(&img, i, j, 0xF40000);
			j++;
		}
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
	 	rotation = 360;
	rotation -= 30;
}

void	draw_player(unsigned int long long str)
{
	float 	i;
	float 	j;
	float	k;
	float	rotationAngle;
	float	moveSpeed;
	float	rotationSpeed;
	float	r;
	float	D;
	
	moveSpeed = 2;
	rotationAngle = M_PI / 180;
	rotationSpeed = rotation + (2 * turn_direction);
	k = rotationSpeed;
	rotation = k;
	if (rotation < 0)
		rotation += 360;
	rotation = rotation % 360;
	if (player.x == 0 && player.y == 0)
	{
		player.x = position.x;
		player.y = position.y;
	}
	i = player.x;
	j = player.y;
	//while (k < rotationSpeed + 60)
	//{
		k = rotationSpeed + 30;
		r = 0;
		while (r < WallHit.Distance) // distance du champ de vision
		{
			j = player.y + (r * sin(k * rotationAngle));
			i = player.x + (r * cos(k * rotationAngle));
			my_mlx_pixel_put(&img, i, j, str);
			r+=0.2;
		}
	//	k+=0.2;
	//}
	my_mlx_pixel_put(&img, player.x, player.y, str);
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
			if ((la_map[i][j] == 'N' || la_map[i][j] == 'W' || la_map[i][j] == 'S' 
				|| la_map[i][j] == 'E') && check_playerdraw == 0)
			{
				ft_checkdirectionplayer(i, j);
				draw_player(0xFFFFFF);
				check_playerdraw = 1;
			}
			position.x = position.x + TILE_SIZE;
			j++;
		}
		position.y = position.y + TILE_SIZE;
		i++;
	}
	position.y = 0;
}

int		nowall(int key)
{
	int	i;
	int	j;
	int	s;
	int	x;
	int	y;

	if (key == -1)
		s = -2;
	if (key == 1)
		s = 2;
	x = player.x + (s * cos ((rotation + 30) * (M_PI / 180)));
	y = player.y + (s * sin ((rotation + 30) * (M_PI / 180)));
	i = y / TILE_SIZE;
	j = x / TILE_SIZE;
	if (la_map[i][j] == '1' || la_map[i][j] == ' ')
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
	if (KEY_PRL1 == 1)
		draw_player(0xFFFFFF);
    if (KEY_PUD1 == 1)
	{
		if (walk_direction == -1 || walk_direction == 1) // down or up
		{
			if (nowall(walk_direction) == 1)
			{
				player.x += 2 * walk_direction * cos ((rotation + 30) * (M_PI / 180));
				player.y += 2 * walk_direction * sin ((rotation + 30) * (M_PI / 180));
			}
		}
		draw_player(0xFFFFFF);
	}
	if (KEY == 1)
        exit(0);
}

int		key_pressed(int key)
{
	if (key == 123 || key == 0 || key == 124 || key == 2)
	{
		KEY_PRL1 = 1;
		if (key == 123 || key == 0) //right
			turn_direction = -1;
		if (key == 124 || key == 2) //left
			turn_direction = 1;
	}
	if (key == 1 || key == 13)
	{
		KEY_PUD1 = 1;
		if (key == 1) // down
			walk_direction = -1;
		if (key == 13) // up
			walk_direction = 1;
	}
	if (key == 53)
		KEY = 1;
	return (0);
}

int		direction_player(void)
{
	mlx_destroy_image(g_mlx_ptr, img.img);
	mlx_clear_window(g_mlx_ptr, g_win_ptr);
	img.img = mlx_new_image(g_mlx_ptr, map.x, map.y);
	ft_draw_map();
	ft_RayCasting();
	ft_draw_player();
	mlx_put_image_to_window(g_mlx_ptr, g_win_ptr, img.img, 0, 0);
	
	//printf("%d\n", turn_direction);
	return(0);
}

void	initialisation()
{
	FOV = 60;
	KEY = 0;
	KEY_PRL1 = 0;
	KEY_PRL = 0;
	KEY_PUD1 = 0;
	KEY_PUD = 0;
	TILE_SIZE = 30;
	check_playerdraw = 0;
	player.x = 0;
	player.y = 0;
	position.x = 0;
	position.y = 0;
	walk_direction = 0;
	turn_direction = 0;
}

int		main()
{
	initialisation();
	ft_readmap();
	g_mlx_ptr = mlx_init();
	g_win_ptr = mlx_new_window(g_mlx_ptr, map.x, map.y, "sboof");
	img.img = mlx_new_image(g_mlx_ptr, map.x, map.y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_hook(g_win_ptr, 2, 0, key_pressed, (void *)0);
	mlx_hook(g_win_ptr, 3, 0, key_released, (void *)0);
	mlx_loop_hook(g_mlx_ptr, direction_player, (void *)0);
	mlx_loop(g_mlx_ptr);
}