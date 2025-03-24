/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 02:39:43 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/24 02:24:47 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

char	**duplicate_map(t_parse *parse, char **map, int *height)
{
	char	**new;
	int		i;

	if (*height <= 0 || !map)
		return (NULL);
	new = ft_calloc(*height + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = -1;
	while (map[++i])
		new[i] = ft_strdup(map[i]);
	i = *height - 1;
	while (i >= 0 && is_empty_line(new[i]))
	{
		free(new[i]);
		free(map[i]);
		map[i] = NULL;
		new[i] = NULL;
		(*height)--;
		i--;
	}
	parse->map_height = *height;
	return (new);
}

char	**ft_read_map(char **arr, char *new, int *size)
{
	char	**new_arr;
	int		i;

	new_arr = malloc(sizeof(char *) * (*size + 2));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (i < *size)
	{
		new_arr[i] = arr[i];
		i++;
	}
	new_arr[i] = ft_strdup(new);
	new_arr[i + 1] = NULL;
	*size += 1;
	free(arr);
	return (new_arr);
}

int	check_valid_map_chars(char *line, char *valid_chars)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(valid_chars, line[i]) && !ft_isspace(line[i]))
			return (ft_error(NULL, "Invalid character in map", &line[i]), 1);
		i++;
	}
	return (0);
}

int	check_zero_space(t_parse *parse)
{
	int	i;
	int	j;

	i = -1;
	while (parse->map[++i])
	{
		j = -1;
		while (parse->map[i][++j])
		{
			if (parse->map[i][j] == '0')
			{
				if (parse->map[i][j + 1] == ' ')
					return (ft_error(parse, "0 ◀", &parse->map[i][j]), 1);
				if (j > 0 && parse->map[i][j - 1] == ' ')
					return (ft_error(parse, "0 ➤", &parse->map[i][j]), 1);
				if (i > 0 && (parse->map[i - 1][j] == ' '
					|| (int)ft_strlen(parse->map[i - 1]) <= j))
					return (ft_error(parse, "0 ▲", &parse->map[i][j]), 1);
				if (parse->map[i + 1] != NULL && (parse->map[i + 1][j] == ' '
					|| (int)ft_strlen(parse->map[i + 1]) <= j))
					return (ft_error(parse, "0 ⬇", &parse->map[i][j]), 1);
			}
		}
	}
	return (0);
}

int	get_map_line(t_parse *parse, char *line)
{
	from_new_line_to_ziroo(line);
	if (check_valid_map_chars(line, parse->valid_set) == 1)
		return (1);
	parse->map = ft_read_map(parse->map, line, &parse->map_height);
	if (!parse->map)
		return (ft_error(parse, "Could not allocate memory", NULL), 1);
	if (check_zero_space(parse) == 1)
		return (1);
	parse->found_map = true;
	return (0);
}
