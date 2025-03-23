/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:15:53 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/23 03:15:55 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_key_flags(t_data *data)
{
	data->keys[RIGHT_FLAG] = 0;
	data->keys[LEFT_FLAG] = 0;
	data->keys[W_FLAG] = 0;
	data->keys[S_FLAG] = 0;
	data->keys[D_FLAG] = 0;
	data->keys[A_FLAG] = 0;
	data->keys[CLOSE_FLAG] = 0;
	data->keys[ROTATE_FLAG] = 0;
	data->keys[MOVE_FLAG] = 0;
}

int	key_press_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		data->keys[CLOSE_FLAG] = 1;
	if (key == XK_Left)
		data->keys[LEFT_FLAG] = 1;
	if (key == XK_Right)
		data->keys[RIGHT_FLAG] = 1;
	if (key == XK_w)
		data->keys[W_FLAG] = 1;
	if (key == XK_a)
		data->keys[A_FLAG] = 1;
	if (key == XK_s)
		data->keys[S_FLAG] = 1;
	if (key == XK_d)
		data->keys[D_FLAG] = 1;
	return (0);
}

int	key_release_handler(int key, t_data *data)
{
	if (key == XK_Left)
		data->keys[LEFT_FLAG] = 0;
	if (key == XK_Right)
		data->keys[RIGHT_FLAG] = 0;
	if (key == XK_w)
		data->keys[W_FLAG] = 0;
	if (key == XK_s)
		data->keys[S_FLAG] = 0;
	if (key == XK_d)
		data->keys[D_FLAG] = 0;
	if (key == XK_a)
		data->keys[A_FLAG] = 0;
	return (0);
}

void	input_handler(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_press_handler, data);
	mlx_hook(data->win, 3, 1L << 1, key_release_handler, data);
	mlx_hook(data->win, 17, 1L << 17, quiter, data);
}
