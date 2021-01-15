/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:15:31 by amaach            #+#    #+#             */
/*   Updated: 2021/01/15 09:50:09 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int				key_released(int key)
{
	if (key == 123 || key == 124)
		g_turn_direction = 0;
	if (key == 1 || key == 13)
		g_walk_direction = 0;
	if (key == 259)
	{
		g_turn_direction = 0;
		g_walk_direction = 0;
	}
	if (key == 0 || key == 2)
	{
		g_sidewalk = 0;
		g_walk_direction = 0;
	}
	return (0);
}

int				key_pressed(int key)
{
	if (key == 123 || key == 124)
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
	if (key == 0 || key == 2)
	{
		g_walk_direction = 1;
		g_sidewalk = (key == 0) ? -90 : 0;
		if (key == 2)
			g_sidewalk = 90;
	}
	if (key == 53)
		g_key = 1;
	return (0);
}

int				direction_player(void)
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

static void		ft_free_textures(void)
{
	free(g_map.we);
	free(g_map.so);
	free(g_map.no);
	free(g_map.ea);
}

void			ft_initia_texture(void)
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
