/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejd <ael-mejd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:16:22 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/23 21:41:49 by ael-mejd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_textures(t_data *data, t_parse *parse)
{
	int	i;
	int	count;

	i = -1;
	count = 4;
	while (++i < 4)
	{
		data->texinfo[i].img = mlx_xpm_file_to_image(data->mlx,
				parse->tex_path[i], &data->texinfo[i].width,
				&data->texinfo[i].hight);
		if (!data->texinfo[i].img)
		{
			ft_error(parse, "Invalid texture", "");
			return ;
		}
		data->texinfo[i].iter = mlx_get_data_addr(data->texinfo[i].img,
				&data->texinfo[i].pixel_bits, &data->texinfo[i].line_length,
				&data->texinfo[i].endianess);
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data->image.addr + (y * data->image.size_line + x * (data->image.bpp
				/ 8));
	*(unsigned int *)dst = color;
}

int	get_cords_color(t_texture *img, int x, int y)
{
	char	*dst;

	dst = img->iter + (y * img->line_length + x * (img->pixel_bits / 8));
	return (*(int *)dst);
}

void	get_texture_color(t_data *data, t_ray *ray, int current_y)
{
	float	x_scale;
	float	y_scale;
	int		current_x;

	current_x = 0;
	x_scale = (float)data->texinfo[ray->texture_idx].width / TILE_SIZE;
	y_scale = (float)data->texinfo[ray->texture_idx].hight / ray->height;
	if (ray->texture_idx == N_INDEX)
		current_x = (int)ray->horizontal_x % TILE_SIZE;
	else if (ray->texture_idx == S_INDEX)
		current_x = TILE_SIZE - ((int)ray->horizontal_x % TILE_SIZE);
	else if (ray->texture_idx == E_INDEX)
		current_x = (int)ray->vertical_y % TILE_SIZE;
	else if (ray->texture_idx == W_INDEX)
		current_x = TILE_SIZE - ((int)ray->vertical_y % TILE_SIZE);
	ray->curr_color = get_cords_color(&data->texinfo[ray->texture_idx],
			current_x * x_scale, current_y * y_scale);
}
