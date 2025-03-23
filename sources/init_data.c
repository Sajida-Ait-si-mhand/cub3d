/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:15:46 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/23 03:15:48 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	player_first_cordinate(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("NSEW", data->map[y][x]))
			{
				data->player.pos_x = (x * TILE_SIZE + TILE_SIZE / 2);
				data->player.pos_y = (y * TILE_SIZE + TILE_SIZE / 2);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_data(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	data->image.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->image.addr = mlx_get_data_addr(data->image.img, &data->image.bpp,
			&data->image.size_line, &data->image.endian);
	data->map_width = data->width * TILE_SIZE;
	data->map_height = data->height * TILE_SIZE;
	player_first_cordinate(data);
	data->player.fov = FOV;
	data->player.distance_to_project_plan = ((float)WIDTH / 2)
		/ tan(radian(data->player.fov / 2));
}

void	first_view(t_data *data)
{
	raycasting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
}

void	merge(t_parse *parse)
{
	t_data	data;

	data.debug = 0;
	data.map = parse->map;
	data.floor = parse->floor_color;
	data.ceil = parse->ceil_color;
	data.height = parse->map_height;
	data.width = parse->map_width;
	data.player.angle = parse->player_angle;
	data.player.angle_step = ((float)(FOV) / (float)WIDTH);
	init_data(&data);
	init_textures(&data, parse);
	parse->map = NULL;
	first_view(&data);
	init_key_flags(&data);
	input_handler(&data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
}
