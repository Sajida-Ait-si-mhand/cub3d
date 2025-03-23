/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_barriers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:15:30 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/23 03:15:31 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_a_wall(t_data *data, int y, int x)
{
	return (data->map[y][x] == '1');
}

int	check_corners(t_data *data, int index_x, int index_y, int px)
{
	int	py;

	px = (data->player.pos_x / TILE_SIZE);
	py = (data->player.pos_y / TILE_SIZE);
	if (px > index_x && py > index_y)
	{
		if (is_a_wall(data, py, (px - 1)) && is_a_wall(data, (py - 1), px))
			return (1);
	}
	else if (px < index_x && py < index_y)
	{
		if (is_a_wall(data, py, (px + 1)) && is_a_wall(data, (py + 1), px))
			return (1);
	}
	else if (px > index_x && py < index_y)
	{
		if (is_a_wall(data, py, (px - 1)) && is_a_wall(data, (py + 1), px))
			return (1);
	}
	else if (px < index_x && py > index_y)
	{
		if (is_a_wall(data, py, (px + 1)) && is_a_wall(data, (py - 1), px))
			return (1);
	}
	return (0);
}

int	check_barriers(t_data *data, float x, float y)
{
	float	new_x;
	float	new_y;
	float	px;
	float	py;

	new_x = data->player.pos_x + x;
	new_y = data->player.pos_y + y;
	px = (new_x / TILE_SIZE) - ((int)new_x % TILE_SIZE == 0
			&& data->player.pos_x > new_x);
	py = (new_y / TILE_SIZE) - ((int)new_y % TILE_SIZE == 0
			&& data->player.pos_y > new_y);
	if (!((int)py < data->map_height && (int)py >= 0 && (int)px >= 0
			&& (int)px < (int)ft_strlen(data->map[(int)py])))
		return (1);
	if (!ft_strchr("NSEW0", data->map[(int)py][(int)px]))
		return (1);
	return (check_corners(data, (int)px, (int)py, 0));
}
