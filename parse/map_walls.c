/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 02:39:58 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/24 02:03:43 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

bool	ft_check_map_borders(t_parse *parse, char **map)
{
	int	i;
	int	width;
	int	first_index;
	int	last_index;

	i = 0;
	while (i < parse->map_height)
	{
		width = ft_strlen(map[i]);
		first_index = 0;
		last_index = width - 1;
		while (map[i][first_index] == ' ' || map[i][first_index] == '\t')
			first_index++;
		while (map[i][last_index] == ' ' || map[i][last_index] == '\n'
			|| map[i][last_index] == '\t')
			last_index--;
		if (map[i][first_index] != '1' || map[i][last_index] != '1')
			return (ft_error(parse, " MAP BORDER", map[i]), false);
		i++;
	}
	return (true);
}

void	calculate_map_width(t_parse *parse, char **map)
{
	int	i;
	int	max_width;
	int	current_width;

	i = 0;
	max_width = 0;
	while (map[i])
	{
		current_width = ft_strlen(map[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	parse->map_width = max_width;
}

bool	check_player_surronding(t_parse *parse, int i, int j)
{
	if (j <= 0 || ft_isspace(parse->map[i][j - 1]))
		return (true);
	if (j >= (int)ft_strlen(parse->map[i]) || ft_isspace(parse->map[i][j + 1]))
		return (true);
	if (i >= parse->map_height || j >= (int)ft_strlen(parse->map[i + 1])
		|| ft_isspace(parse->map[i + 1][j]))
		return (true);
	parse->player_x = j;
	parse->player_y = i;
	parse->player_dir = parse->map[i][j];
	if (parse->player_dir == 'W')
		parse->player_angle = 180;
	if (parse->player_dir == 'N')
		parse->player_angle = 270;
	if (parse->player_dir == 'E')
		parse->player_angle = 0;
	if (parse->player_dir == 'S')
		parse->player_angle = 90;
	return (false);
}

bool	check_player(t_parse *parse)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (parse->map[++i])
	{
		j = -1;
		while (parse->map[i][++j])
		{
			if (ft_strchr("NEWS", parse->map[i][j]))
			{
				if (check_player_surronding(parse, i, j))
					return (false);
				count++;
			}
		}
	}
	if (count != 1)
		return (false);
	return (true);
}
