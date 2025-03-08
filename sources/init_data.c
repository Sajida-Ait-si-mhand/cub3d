#include "../cub3d.h"

void    player_first_corrdinate(t_data *data)
{
    int x;
    int y;

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

void init_data(t_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
    data->image.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->image.addr = mlx_get_data_addr(data->image.img, &data->image.bpp, &data->image.size_line, &data->image.endian);
    data->width = data->map_width * TILE_SIZE;
    data->height = data->map_height * TILE_SIZE;
    player_first_cordinate(data);
    data->player.fov = FOV;
    data->player.distance = ((float)WIDTH / 2) / tan(radian(data->player.fov / 2));
}

void merge(t_tinfo *info)
{
    t_data data;

    data.map = info->dbl_ptr;
    // data.ceilieng_color = info->baqa ma3mlata;
    // data.floor_color = info-> baqa ma3mlata
    data.map_height = info->hieght;
    data.map_width = info->width;
    // data.player.angle = info-> baqa ma3mlata
    data.player.angle_step = ((float)FOV / (float)WIDTH);
    init_data(&data);
    init_data(&data, info);
    info->dbl_ptr = NULL;
    input_handler(&data);
}