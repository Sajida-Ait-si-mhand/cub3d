#include "../cub3d.h"

float calculate_delta_x(t_data *data, float *vertical_x, float *vertical_y, float rayangle)
{
    float delta_x;

    if (rayangle > 90 && rayangle < 270)
    {
        if (*vertical_x == data->player.pos_x && *vertical_y == data->player.pos_y)
        {
            delta_x = *vertical_x - (((int)(*vertical_x / TILE_SIZE)) * TILE_SIZE);
            if (delta_x == 0)
                delta_x = TILE_SIZE;
        }
        else
            delta_x = TILE_SIZE;
    }
    else
    {
        if (*vertical_x == data->player.pos_x && *vertical_y == data->player.pos_y)
            delta_x = *vertical_x - (((int)(*vertical_x / TILE_SIZE) + 1) * TILE_SIZE);
        else
            delta_x = -TILE_SIZE;
    }
    return (delta_x);
}

void find_vertical_point(t_data *data, float rayangle, float *vertical_x, float *vertical_y)
{
    float delta_x;
    float delta_y;

    if (rayangle == 90 || rayangle == 270)
        return;
    delta_x = calculate_delta_x(data, vertical_x, vertical_y, rayangle);
    delta_y = tan(radian(rayangle)) * delta_x;
    *vertical_x = *vertical_x - delta_x;
    *vertical_y = *vertical_y - delta_y;
}

static int check_next_position(t_data *data, t_ray *ray, int *x, int *y)
{
    float check_x;

    if (ray->rayangle == 90 || ray->rayangle == 270 || ray->vertical_x < 0 || ray->vertical_x > data->map_width || ray->vertical_y < 0 || ray->vertical_y > data->map_height)
        return (1);
    check_x = ray->vertical_x;
    if (ray->vertical_x < data->player.pos_x)
        check_x -= 1;
    *x = check_x / TILE_SIZE;
    *y = ray->vertical_y / TILE_SIZE;
    if ((*y < data->map_height && *y >= 0) && (*x >= 0 && *x < (int)ft_strlen(data->map[*y])))
    {
        if (data->map[*y][*x] == ' ')
            return (1);
    }
    else
        return (1);
    return (0);
}

void vertical(t_data *data, t_ray *ray, float rayangle)
{
    int x;
    int y;

    ray->vertical_y = data->player.pos_y;
    ray->vertical_x = data->player.pos_x;
    ray->vertical_distance = -1.0;
    while (1)
    {
        find_vertical_point(data, rayangle, &ray->vertical_x, &ray->vertical_y);
        if (check_next_position(data, ray, &x, &y))
            break;
        if (data->map[y][x] == '1')
        {
            ray->vertical_distance = get_distance(data, ray->vertical_x, ray->vertical_y);
            break;
        }
    }
}
