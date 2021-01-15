/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 14:35:21 by amaach            #+#    #+#             */
/*   Updated: 2021/01/15 09:46:19 by amaach           ###   ########.fr       */
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
	g_sidewalk = 0;
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

int		ft_exit_x(void)
{
	exit(0);
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
}
