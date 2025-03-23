/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:15:59 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/23 03:16:01 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	w_moves(t_data *data)
{
	float	delta_x;
	float	delta_y;
	float	speed;

	if (data->keys[W_FLAG])
	{
		speed = (float)TILE_SIZE / SPEED_DIVISOR;
		delta_x = (cos(radian(data->player.angle)) * speed);
		delta_y = (sin(radian(data->player.angle)) * speed);
		if (delta_x < 0.00001 && delta_x > -0.00001)
			delta_x = 0;
		if (delta_y < 0.00001 && delta_y > -0.00001)
			delta_y = 0;
		if (check_barriers(data, delta_x, delta_y))
			return ;
		data->player.pos_x += delta_x;
		data->player.pos_y += delta_y;
		data->keys[MOVE_FLAG] = 1;
	}
}

void	s_moves(t_data *data)
{
	float	delta_x;
	float	delta_y;
	float	speed;

	if (data->keys[S_FLAG])
	{
		speed = (float)TILE_SIZE / SPEED_DIVISOR;
		delta_x = (cos(radian(data->player.angle)) * speed) * -1;
		delta_y = (sin(radian(data->player.angle)) * speed) * -1;
		if (delta_x < 0.00001 && delta_x > -0.00001)
			delta_x = 0;
		if (delta_y < 0.00001 && delta_y > -0.00001)
			delta_y = 0;
		if (check_barriers(data, delta_x, delta_y))
			return ;
		data->player.pos_x += delta_x;
		data->player.pos_y += delta_y;
		data->keys[MOVE_FLAG] = 1;
	}
}

void	d_moves(t_data *data)
{
	float	delta_x;
	float	delta_y;
	float	speed;

	if (data->keys[D_FLAG])
	{
		speed = (float)TILE_SIZE / SPEED_DIVISOR;
		delta_x = (sin(radian(data->player.angle)) * speed) * -1;
		delta_y = (cos(radian(data->player.angle)) * speed);
		if (delta_x < 0.00001 && delta_x > -0.00001)
			delta_x = 0;
		if (delta_y < 0.00001 && delta_y > -0.00001)
			delta_y = 0;
		if (check_barriers(data, delta_x, delta_y))
			return ;
		data->player.pos_x += delta_x;
		data->player.pos_y += delta_y;
		data->keys[MOVE_FLAG] = 1;
	}
}

void	a_moves(t_data *data)
{
	float	delta_x;
	float	delta_y;
	float	speed;

	if (data->keys[A_FLAG])
	{
		speed = (float)TILE_SIZE / SPEED_DIVISOR;
		delta_x = (sin(radian(data->player.angle)) * speed);
		delta_y = (cos(radian(data->player.angle)) * speed) * -1;
		if (delta_x < 0.00001 && delta_x > -0.00001)
			delta_x = 0;
		if (delta_y < 0.00001 && delta_y > -0.00001)
			delta_y = 0;
		if (check_barriers(data, delta_x, delta_y))
			return ;
		data->player.pos_x += delta_x;
		data->player.pos_y += delta_y;
		data->keys[MOVE_FLAG] = true;
	}
}

void	move_player(t_data *data)
{
	if (!data->keys[W_FLAG] && !data->keys[S_FLAG] && !data->keys[D_FLAG]
		&& !data->keys[A_FLAG])
		return ;
	w_moves(data);
	s_moves(data);
	d_moves(data);
	a_moves(data);
}
