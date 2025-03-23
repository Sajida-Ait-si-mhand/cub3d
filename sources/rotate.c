/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:16:13 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/23 03:16:14 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	radian(float degree)
{
	return (degree * M_PI / 180);
}

void	rotate(t_data *data)
{
	if (!data->keys[RIGHT_FLAG] && !data->keys[LEFT_FLAG])
		return ;
	if (data->keys[RIGHT_FLAG])
	{
		data->player.angle += ANGLE;
		if (data->player.angle >= 360)
			data->player.angle -= 360;
	}
	if (data->keys[LEFT_FLAG])
	{
		data->player.angle -= ANGLE;
		if (data->player.angle < 0)
			data->player.angle += 360;
	}
	data->keys[ROTATE_FLAG] = 1;
}
