/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejd <ael-mejd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 02:40:12 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/24 03:37:28 by ael-mejd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

static int	handle_pre_map_content(t_parse *parse, char *line)
{
	while (parse->flag != 6 && (*line == ' ' || *line == '\t'))
		line++;
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
		return (parse->flag++, parse_textures(parse, line));
	if (ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
		return (parse->flag++, ft_color(parse, line));
	if (parse->flag >= 6)
	{
		if (parse->floor_color != -1 && parse->ceil_color != -1
			&& ft_strchr("01NSWE ", *line))
			return (get_map_line(parse, line));
	}
	return (ft_error(parse, "Invalid configuration", line), 1);
}

static int	handle_line(t_parse *parse, char *line)
{
	if (!parse->found_map && !is_empty_line(line))
	{
		if (handle_pre_map_content(parse, line))
			return (free_parser(&parse), close(parse->fd), free(line), 1);
	}
	else if (parse->found_map && get_map_line(parse, line))
	{
		return (close(parse->fd), free(line), 1);
	}
	return (0);
}

int	ft_parse(t_parse *parse)
{
	char	*line;

	parse->flag = 0;
	line = get_next_line(parse->fd);
	if (!line)
		return (ft_error(parse, "Empty file", NULL), close(parse->fd), 1);
	while (line)
	{
		if (handle_line(parse, line))
		{
			free(line);
			get_next_line(parse->fd);
			return (1);
		}
		free(line);
		line = get_next_line(parse->fd);
	}
	return (validate_and_close(parse));
}
