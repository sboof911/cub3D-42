// #include "cub3d.h"

// int		key_released(int key)
// {
// 	if (key == 123 || key == 124 || key == 2 || key == 0)
// 		turn_direction = 0;
// 	if (key == 1 || key == 13)
// 		walk_direction = 0;
// 	return (0);
// }

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
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
// 	int		K;
	
// 	K = 1;
// 	moveSpeed = 2;
// 	rotationAngle = M_PI / 180;
// 	 if (str == 0x000000)
// 	 	K = 0;
// 	rotationSpeed = rotation + (2 * turn_direction * K);
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
// 			my_mlx_pixel_put(&img, i, j, str);
// 			r+=0.2;
// 		}
// 		k+=0.2;
// 	}
// 	my_mlx_pixel_put(&img, player->x, player->y, str);
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
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	ft_draw_map(void)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	position->x = 0;
// 	position->y = 0;
// 	printf("\n\n\n%d\n\n\n\n", check_playerdraw);
// 	while (la_map[i] != 0)
// 	{
// 		position->x = 0;
// 		j = 0;
// 		while (la_map[i][j] != '\0')
// 		{
// 			if (la_map[i][j] == '1')
// 				draw_tile();
// 			if (la_map[i][j] == 'N' && check_playerdraw == 0)
// 			{
// 				draw_player(0xFFFFFF);
// 				check_playerdraw = 1;
// 			}
// 			position->x = position->x + 30;
// 			j++;
// 		}
// 		position->y = position->y + 30;
// 		i++;
// 	}
// }

// int		nowall(int key)
// {
// 	int	i;
// 	int	j;
// 	int	s;
// 	int	x;
// 	int	y;

// 	if (key == -1)
// 		s = -2;
// 	if (key == 1)
// 		s = 2;
// 	x = player->x + (s * cos ((rotation + 30) * (M_PI / 180)));
// 	y = player->y + (s * sin ((rotation + 30) * (M_PI / 180)));
// 	i = y / 30;
// 	j = x / 30;
// 	if (la_map[i][j] == '1' || la_map[i][j] == ' ')
// 		return (0);
// 	return (1);
// }

// int		key_pressed(int key)
// {
// 	if (key == 123 || key == 0 || key == 124 || key == 2)
// 	{
// 		KEY_PRL1 = 1;
// 		if (key == 123 || key == 0) //right
// 			turn_direction = -1;
// 		if (key == 124 || key == 2) //left
// 			turn_direction = 1;
// 	}
// 	if (key == 1 || key == 13)
// 	{
// 		KEY_PUD1 = 1;
// 		if (key == 1) // down
// 			walk_direction = -1;
// 		if (key == 13) // up
// 			walk_direction = 1;
// 	}
// 	if (key == 53)
// 		KEY = 1;
// 	return (0);
// }

// void	ft_draw_player(void)
// {
// 	if (KEY_PRL1 == 1)
//     {
//         draw_player(0x000000);
// 		draw_player(0xFFFFFF);
//     }
//     if (KEY_PUD1 == 1)
// 	{
// 		draw_player(0x000000);
// 		if (walk_direction == -1) // down
// 		{
// 			if (nowall(walk_direction) == 1)
// 			{
// 				player->x += 2 * walk_direction * cos ((rotation + 30) * (M_PI / 180));
// 				player->y += 2 * walk_direction * sin ((rotation + 30) * (M_PI / 180));
// 			}
// 		}
// 		if (walk_direction == 1) //up
// 		{
// 			if (nowall(walk_direction) == 1)
// 			{
// 				player->x += 2 * walk_direction * cos ((rotation + 30) * (M_PI / 180));
// 				player->y += 2 * walk_direction * sin ((rotation + 30) * (M_PI / 180));
// 			}
// 		}
// 		draw_player(0xFFFFFF);
// 	}
// 	if (KEY == 1)
//         exit(0);
// }

// int		direction_player(void)
// {
// 	//ft_draw_map();
// 	mlx_hook(okey->windows, 2, 0, key_pressed, (void *)0);
// 	mlx_hook(okey->windows, 3, 0, key_released, (void *)0);
// 	ft_draw_player();
// 	//ft_draw_map();
// 	player->x = player->x;
// 	player->y = player->y;
// 	//printf("\n\n\n%d\n\n\n\n", check_playerdraw);
// 	//mlx_destroy_image(okey->init, img.img);
// 	//ft_draw_map();
// 	//ft_draw_player();
// 	// mlx_hook(okey->windows, 3, 0, &key_released, (void *)0);
// 	mlx_clear_window(okey->init, okey->windows);
// 	ft_draw_map();
// 	//ft_draw_player();
// 	mlx_put_image_to_window(okey->init, okey->windows, img.img, 0, 0);
// 	//mlx_destroy_image(okey->init, img.img);
// 	// ft_draw_map();
// 	return(0);
// }

// /*void	draw_circle(void)
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
// }*/

// int		main()
// {
// 	int		i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	turn_direction = 0;
// 	walk_direction = 0;
// 	KEY = 0;
// 	KEY_PRL1 = 0;
// 	KEY_PUD1 = 0;
// 	KEY_PUD = 0;
// 	KEY_PRL = 0;
// 	check_playerdraw = 0;
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
// 	ft_draw_map();
// 	/*while (la_map[i] != 0)
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
// 	}*/
// 	i = 0;
// 	while (la_map[i] != '\0')
// 	{
// 		j = 0;
// 		printf("$");
// 		while (la_map[i][j] != '\0')
// 		{
// 			printf("%c", la_map[i][j]);
// 			j++;
// 		}
// 		printf("$");
// 		printf("\n");
// 		i++;
// 	}
// 	mlx_loop_hook(okey->windows, direction_player, (void *)0);
// 	//mlx_destroy_image(okey->init, okey->windows);
// 	mlx_loop(okey->init);
// 	return (0);
// }
