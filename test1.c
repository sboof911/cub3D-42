
// #include "cub3d.h"

// int		nowall(int key)
// {
// 	int	i;
// 	int	j;
// 	int	s;
// 	int	x;
// 	int	y;

// 	if (key == 1)
// 		s = -2;
// 	if (key == 13)
// 		s = 2;
// 	x = player->x + (s * cos ((rotation + 30) * (M_PI / 180)));
// 	y = player->y + (s * sin ((rotation + 30) * (M_PI / 180)));
// 	i = y / 30;
// 	j = x / 30;
// 	if (la_map[i][j] != '1')
// 		return (1);
// 	return (0);
// }

// void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
//     char    *dst;

//     dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
//     *(unsigned int*)dst = color;
// }

// void	draw_player(unsigned int long long str)
// {
// 	float 	i;
// 	float 	j;
// 	float	k;
// 	float	rotationAngle;
// 	float	moveSpeed;
// 	float	rotationSpeed;
// 	float	r;
	
// 	moveSpeed = 2;
// 	rotationAngle = M_PI / 180;
// 	if (str == 0x000000)
// 		turn_direction = 0;
// 	rotationSpeed = rotation + (2 * turn_direction);
// 	k = rotationSpeed;
// 	rotation = k;
// 	if (player->x == 0 && player->y == 0)
// 	{
// 		player->x = position->x;
// 		player->y = position->y;
// 	}
// 	i = player->x;
// 	j = player->y;
// 	while (k < rotationSpeed + 60)
// 	{
		
// 		r = 0;
// 		while (r < 10)
// 		{
// 			j = player->y + (r * sin(k * rotationAngle));
// 			i = player->x + (r * cos(k * rotationAngle));
// 			mlx_pixel_put(okey->init, okey->windows, i, j, str);
// 			r+=0.2;
// 		}
// 		k+=0.2;
// 	}
// 	mlx_pixel_put(okey->init, okey->windows, player->x, player->y, str);
// }

// int		direction_player(int key, void *param)
// {
// 	printf("the key is %d********\n", key);
// 	if (key == 123) // left
// 	{
// 		printf("la Rotation est : %d****** \n", rotation);
// 		draw_player(0x000000);
// 		//player->x += -2 * cos ((rotation) * (M_PI / 180));
// 		//player->y += -2 * sin ((rotation + 30) * (M_PI / 180));
// 		draw_player(0xFFFFFF);
// 	}
// 	if (key == 124) // right
// 	{
// 		printf("la Rotation est : %d****** \n", rotation);
// 		draw_player(0x000000);
// 		//player->x += 2 * cos ((rotation) * (M_PI / 180));
// 		//player->y += 2 * sin ((rotation + 30) * (M_PI / 180));
// 		draw_player(0xFFFFFF);
// 	}
// 	if (key == 1) // down
// 	{
// 		draw_player(0x000000);
// 		if (nowall(key) == 1)
// 		{
// 			player->x += -2 * cos ((rotation + 30) * (M_PI / 180));
// 			player->y += -2 * sin ((rotation + 30) * (M_PI / 180));
// 		}
// 		draw_player(0xFFFFFF);
// 	}
// 	if (key == 13) // up
// 	{
// 		draw_player(0x000000);
// 		if (nowall(key) == 1)
// 		{
// 			player->x += 2 * cos ((rotation + 30) * (M_PI / 180));
// 			player->y += 2 * sin ((rotation + 30) * (M_PI / 180));
// 		}
// 		draw_player(0xFFFFFF);
// 	}
// 	if (key == 53) // echap
// 	 	exit(0);
// 	// if (key == 65361) // vision left
// 	// {
// 	// 	draw_player(0x000000);
// 	// 	direction = -1;
// 	// 	draw_player(0xFFFFFF);
// 	// }
// 	// if (key == 65363) // vision right
// 	// {
// 	// 	draw_player(0x000000);
// 	// 	direction = 1;
// 	// 	draw_player(0xFFFFFF);	
// 	// }
// 	return(0);
// }

// void	draw_tile(void)
// {
// 	float i;
// 	float j;
	
	
// 	i = position->x;
// 	j = position->y;
// 	while (i <= position->x + 30)
// 	{
// 		j = position->y;
// 		while (j <= position->y + 30)
// 		{
// 			my_mlx_pixel_put(&img, i, j, 0xF40000);
// 			//mlx_pixel_put(okey->init, okey->windows, i, j, 0xF40000);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	draw_circle(void)
// {
// 	float 	i;
// 	float 	j;
// 	float	k;
// 	float	rotationAngle;
// 	float	moveSpeed;
// 	float	rotationSpeed;
// 	float	r;

// 	moveSpeed = 2;
// 	rotationAngle = M_PI / 180;
// 	k = 0;
// 	i = position->x;
// 	j = position->y;
// 	while (k < 360)
// 	{
		
// 		r = 0;
// 		while (r < 10)
// 		{
// 			j = position->y + (r * sin(k * rotationAngle));
// 			i = position->x + (r * cos(k * rotationAngle));
// 			mlx_pixel_put(okey->init, okey->windows, i, j, 0xFFFFFF);
// 			r+=0.2;
// 		}
// 		k+=0.2;
// 	}
// }

// int		main()
// {
// 	int		i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	if (!(okey = malloc(sizeof(t_maps))))
// 		return (-1);
// 	if (!(position = malloc(sizeof(t_point))))
// 		return (-1);
// 	if (!(player = malloc(sizeof(t_point))))
// 		return (-1);
// 	position->x = 0;
// 	position->y = 0;
// 	player->x = 0;
// 	player->y = 0;
// 	turn_direction = 0;
// 	rotation = 240;
// 	okey->init = mlx_init();
// 	ft_readmap();
// 	okey->windows = mlx_new_window(okey->init, map->x, map->y, "sboof");
// 	img.img = mlx_new_image(okey->init, map->x, map->y);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
// 	while (la_map[i] != 0)
// 	{
// 		position->x = 0;
// 		j = 0;
// 		while (la_map[i][j] != '\0')
// 		{
// 			if (la_map[i][j] == '1')
// 				draw_tile();
// 			if (la_map[i][j] == 'N')
// 				draw_player(0xFFFFFF);
// 			position->x = position->x + 30;
// 			j++;
// 		}
// 		position->y = position->y + 30;
// 		i++;
// 	}
// 	mlx_put_image_to_window(okey->init, okey->windows, img.img, 0, 0);
// 	mlx_key_hook(okey->windows, direction_player, (void *)0);
// 	mlx_loop(okey->init);
// 	return (0);
// }
// /*
// int		key_released(int key)
// {
// 	if (key == 123 || key == 124)
// 		KEY_PLR1 = 0;
// 	if (key == 1 || key == 13)
// 		key_PUD1 = 0;
// 	return (0);
// }
// int		key_pressed(int key)
// {
// 	if (key == 123 || key == 124)
// 	{
// 		KEY_PLR = key;
// 		KEY_PLR1 = 1;
// 	}
// 	if (key == 1 || key == 13)
// 	{
// 		KEY_PUD = key;
// 		key_PUD1 = 1;
// 	}
// 	return (0);
// }
// mlx_hook(okey->windows, 2, 0, &key_pressed);
// mlx_hook(okey->windows, 2, 0, &key_pressed);
