

#ifndef CUB3D_H
#define CUB3D_H


#define WIDTH 1280
#define HEIGHT 620
# define MOVESPEED 0.0125
# define ROTSPEED 0.015
# define TILE_SIZE 1000
# define SPEED_DIVISOR 25
# define FOV 60

# define RIGHT_FLAG 0
# define LEFT_FLAG 1
# define W_FLAG 2
# define S_FLAG 3
# define D_FLAG 4
# define A_FLAG 5
# define CLOSE_FLAG 6
# define ROTATE_FLAG 7
# define MOVE_FLAG 8
# define KEYS_NB 9
# define ANGLE 1.5

# define N_INDEX 0
# define S_INDEX 1
# define W_INDEX 2
# define E_INDEX 3

# define ERR_MALLOC "Could not allocate memory"

#include "parsing.h"
#include <mlx.h>
#include <math.h>
#include <stdbool.h>
# include <errno.h>
#include <X11/keysym.h>
#include <X11/X.h>


typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_ray
{
	float	colums;
	float	distance;
	float	rayangle;
	float	raystep;
	float	horizontal_x;
	float	horizontal_y;
	float	horizontal_distance;
	float	vertical_x;
	float	vertical_y;
	float	vertical_distance;
	int		side_flag;
	int		curr_color;
	int		texture_idx;
	float	height;
}	t_ray;

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	angle;
	float	fov;
	float	angle_step;
	float	distance_to_project_plan;
	float	first_x_fov;
	float	last_x_fov;
	float	first_y_fov;
	float	last_y_fov;
}	t_player;

typedef struct s_texture
{
	void	*img;
	char	*iter;
	int		line_length;
	int		pixel_bits;
	int		endianess;
	int		width;
	int		hight;
}	t_texture;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			height;
	int			width;
	int			map_height;
	int			map_width;
	char		**map;
	int			ceilieng_color[3];
	int			floor_color[3];
	int 		keys[KEYS_NB];
	t_player	player;
	t_ray		ray;
	t_img		image;
	t_texture	texinfo[4];
}	t_data;

enum e_texture_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};


void init_textures(t_data *data, t_tinfo *info);
int	quiter(t_data *data);
void	input_handler(t_data *data);
float	radian(float degree);
void	rotate(t_data *data);
void	horizontal(t_data *data, t_ray *ray, float rayangle);
void vertical(t_data *data, t_ray *ray, float rayangle);
float get_distance(t_data *data, float x, float y);
void raycasting(t_data *data);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
void get_texture_color(t_data *data, t_ray *ray, int current_y);
void merge(t_tinfo *info, t_textura *tex);
void free_texture(void *mlx, t_texture *texture);
void    free_map(char **map);
void	move_player(t_data *data);
int render(t_data *data);
#endif