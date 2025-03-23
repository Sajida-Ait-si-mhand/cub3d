/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:14:40 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/23 03:14:42 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NEW_H
# define NEW_H

// # include "cub3d.h"
# include "../get_next_line/get_next_line.h"
# include "../include/color.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

typedef struct s_parse
{
	char	*file_name;
	char	*valid_set;
	char	**map;
	int		map_height;
	int		map_width;
	char	*no_text;
	char	*so_text;
	char	*we_text;
	char	*ea_text;
	char	*tex_path[4];
	int		floor_color;
	int		ceil_color;
	char	player_dir;
	int		player_x;
	int		player_y;
	int		fd;
	bool	found_map;
	int		texture_count;
	int		consecutive_blanks;
	float	player_angle;
}			t_parse;

int			ft_parse(t_parse *parse);
char		**duplicate_map(t_parse *parse, char **map, int *height);
void		free_mapping(char **str);
bool		validate_map(t_parse *parse);
bool		check_player(t_parse *parse);
void		free_parser(t_parse *parse);
int			print_err(char *info, char *str, int code);
int			get_map_line(t_parse *parse, char *line);
bool		is_empty_line(char *line);
int			parse_textures(t_parse *parse, char *line);
bool		ft_check_map_borders(t_parse *parse, char **map);
int			validate_and_close(t_parse *parse);

#endif