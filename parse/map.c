/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 02:40:05 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/23 03:13:23 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

bool	check_f_and_last_line(char **line, int height)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	while (line[0][f])
	{
		if (line[0][f] == '0')
			return (ft_error("👾 YOU NEED '1' IN FIRST ROW 👾", line[0]), false);
		f++;
	}
	f = 0;
	while (line[height - 1][f])
	{
		if (line[height - 1][f] == '0')
			return (ft_error("👾 YOU NEED '1' IN LAST ROW 👾", line[height - 1]),
				false);
		f++;
	}
	return (true);
}

bool	ft_check_map_spaces_above_zero(t_parse *parse, char **map)
{
	int	i;
	int	j;

	i = 1;
	while (i < parse->map_height)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (map[i - 1][j] == ' ')
					return (ft_error("MAP ERROR: Space above '0' detected!",
							map[i]), false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	validate_map(t_parse *parse)
{
	char	**copy;

	copy = duplicate_map(parse, parse->map, &parse->map_height);
	if (!copy)
		return (false);
	if (parse->map_height < 3)
		return (false);
	if (!ft_check_map_borders(parse, copy))
		return (printf("here1"), free_mapping(copy), false);
	if (!check_f_and_last_line(copy, parse->map_height))
		return (printf("here2"), free_mapping(copy), false);
	if (!check_player(parse))
		return (printf("here3"), free_mapping(copy), false);
	calculate_map_width(parse, copy);
	return (free_mapping(copy), true);
}

int	validate_and_close(t_parse *parse)
{
	if (!validate_map(parse))
	{
		close(parse->fd);
		return (print_err(NULL, "Invalid map", 1));
	}
	if (parse->texture_count != 4 || parse->floor_color == -1
		|| parse->ceil_color == -1)
	{
		close(parse->fd);
		return (print_err(NULL, "Missing required configurations", 1));
	}
	return (close(parse->fd), 0);
}
