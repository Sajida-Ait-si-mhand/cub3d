/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:15:35 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/23 03:15:37 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_texture(void *mlx, t_texture *texture)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(mlx, texture[i].img);
		i++;
	}
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

void	free_textura(t_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (data->texinfo[i].img)
			mlx_destroy_image(data->mlx, data->texinfo[i].img);
		i++;
	}
}

void	free_all(t_data *data)
{
	if (data->image.img)
		mlx_destroy_image(data->mlx, data->image.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}
