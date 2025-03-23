/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 02:40:19 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/23 04:31:54 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

char	*get_texture_path(char *path)
{
	int		len;
	char	*line;

	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".xpm", 4))
		return (print_err(NULL, "Invalid texture path (must be .xpm)", 1),
			NULL);
	line = ft_strdup(path);
	if (!line)
		return (NULL);
	return (line);
}

int	fill_textures_paths(t_parse *parse, char *path, char c)
{
	char	*texture_path;

	texture_path = get_texture_path(path);
	if (!texture_path)
		return (1);
	if (c == 'N' && !parse->no_text)
		parse->tex_path[0] = texture_path;
	else if (c == 'S' && !parse->so_text)
		parse->tex_path[1] = texture_path;
	else if (c == 'W' && !parse->we_text)
		parse->tex_path[2] = texture_path;
	else if (c == 'E' && !parse->ea_text)
		parse->tex_path[3] = texture_path;
	else
		return (free(texture_path), 1);
	return (0);
}

int	parse_textures(t_parse *parse, char *line)
{
	char	identifier;
	char	*path;

	while (*line == ' ' || *line == '\t')
		line++;
	parse->texture_count++;
	if (parse->texture_count > 4)
		return (print_err(NULL, "Too many textures", 1));
	while (*line == ' ' || *line == '\t')
		line++;
	if (!(*line) || !(*(line + 1)))
		return (ft_error("Invalid texture line", NULL), 1);
	identifier = *line;
	line += 2;
	while (*line == ' ' || *line == '\t')
		line++;
	if (!(*line))
		return (ft_error("Invalid texture line", NULL), 1);
	path = ft_strtrim(line, " \t\r\n");
	if (!path)
		return (1);
	if (fill_textures_paths(parse, path, identifier))
		return (free(path), 1);
	free(path);
	return (0);
}
