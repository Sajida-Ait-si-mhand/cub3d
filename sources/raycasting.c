#include "../cub3d.h"

void real_distance(t_ray *ray, t_data *data)
{
    if (ray->horizontal_distance != -1)
        ray->horizontal_distance = cos(radian(ray->rayangle - data->player.angle)) * ray->horizontal_distance;
    if (ray->vertical_distance != -1)
        ray->vertical_distance = cos(radian(ray->rayangle - data->player.angle)) * ray->vertical_distance;
}

void small_distance(t_ray *ray)
{
    if (ray->horizontal_distance == -1)
	{
		ray->side_flag = 2;
		ray->distance = ray->vertical_distance;
	}
	else if (ray->vertical_distance == -1)
	{
		ray->side_flag = 1;
		ray->distance = ray->horizontal_distance;
	}
	else if (ray->vertical_distance <= ray->horizontal_distance)
	{
		ray->side_flag = 2;
		ray->distance = ray->vertical_distance;
	}
	else if (ray->horizontal_distance < ray->vertical_distance)
	{
		ray->side_flag = 1;
		ray->distance = ray->horizontal_distance;
	}
}

void height_and_texture(t_data *data, t_ray *ray)
{
    if (ray->side_flag == 1)
    {
        if (ray->rayangle >= 180)
            ray->texture_idx = S_INDEX;
        else
            ray->texture_idx = N_INDEX;
    }
    else
    {
        if ((ray->rayangle >= 0 && ray->rayangle <= 90) || ray->rayangle >= 270)
            ray->texture_idx = W_INDEX;
        else
            ray->texture_idx = E_INDEX;
    }
    if (ray->distance <= 0.0001)
        ray->distance = 0.0001;
    ray->height = (TILE_SIZE / ray->distance) * data->player.distance_to_project_plan;
}

void	draw_column(t_data *data, t_ray *ray, int column)
{
	int	start;
	int	end;
	int	i;

	height_and_texture(data, ray);
	start = (HEIGHT - ray->height) / 2;
	end = start + ray->height;
	if (end > HEIGHT)
		end = HEIGHT;
	i = -1;
	while (++i < start)
		my_mlx_pixel_put(data, column, i, data->ceil);
	i = -1;
	if (start > 0)
		i = start - 1;
	while (++i < end)
	{
		get_texture_color(data, ray, i - start);
		my_mlx_pixel_put(data, column, i, ray->curr_color);
	}
	while (i < HEIGHT)
		my_mlx_pixel_put(data, column, i++, data->floor);
}

// Normalize angle to be between 0 and 360
float normalize_angle(float angle)
{
    while (angle < 0)
        angle += 360;
    while (angle >= 360)
        angle -= 360;
    return angle;
}


void raycasting(t_data *data)
{
    t_ray ray;
    int column;

    column = 0;
    memset(&ray, 0, sizeof(t_ray));
    ray.rayangle = normalize_angle(data->player.angle - (data->player.fov / 2)); //45 - 60/2 = 15
    while (column <= WIDTH)
    {
        horizontal(data, &ray, ray.rayangle);
        vertical(data, &ray, ray.rayangle);
        real_distance(&ray, data);
        small_distance(&ray);
        draw_column(data, &ray, column);
        column++;
        ray.rayangle = normalize_angle(ray.rayangle + data->player.angle_step);
    }
}
