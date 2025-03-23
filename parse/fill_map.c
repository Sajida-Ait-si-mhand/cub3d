/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 02:39:43 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/23 05:17:41 by saait-si         ###   ########.fr       */
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
		printf("new_arr-> %s\n", new_arr[i]);
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
		if (!ft_strchr(valid_chars, line[i]) && !ft_isspace(line[i]) )
			return (ft_error("Invalid character in map", &line[i]), 1);
		i++;
	}
	return (0);
}

int	check_zero_space(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0')
			{
				// printf("map ->>>>> %s\n", map[i]);
				if ( map[i][j + 1] == ' ')
					return (ft_error(" '0' space in right",
							&map[i][j]), 1);
				if (j > 0 && map[i][j - 1] == ' ')
					return (ft_error(" '0' space in left",
							&map[i][j]), 1);
				if (i > 0 && (map[i - 1][j] == ' ' || (int)ft_strlen(map[i - 1]) <= j))
				{
					// printf("map above ->>>>> %s\n", map[i - 1]);
					// printf("map below ->>>>> %s\n", map[i]);
					// printf("j ->>>>> %d\n", j);
					// printf("i ->>>>> %d\n", i);
					// printf("len--------> %lu\n",ft_strlen(map[i - 1]));
					return (ft_error(" '0' space in above", &map[i][j]), 1);
				}
				if (map[i + 1] != NULL && (map[i + 1][j] == ' ' || (int)ft_strlen(map[i + 1]) <= j))
				{
					printf("new_arr->          %s\n", map[i + 1]);
					return (ft_error(" '0' space in below", &map[i][j]), 1);
				}
			}
		}
		printf("--------------------------------------------\n");
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
		return (ft_error("Could not allocate memory", NULL), 1);
	if (check_zero_space(parse->map) == 1)
		return (1);
	parse->found_map = true;
	return (0);
}
