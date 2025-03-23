/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adding_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:15:24 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/23 03:15:25 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	clean_exit(t_data *data, int code)
{
	free_texture(data->mlx, data->texinfo);
	mlx_destroy_image(data->mlx, data->image.img);
	mlx_destroy_window(data->mlx, data->win);
	free_map(data->map);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(code);
}

int	quiter(t_data *data)
{
	clean_exit(data, 0);
	return (0);
}
