/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 02:39:50 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/23 03:08:55 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

bool	is_empty_line(char *line)
{
	if (!line)
		return (true);
	while (*line)
	{
		if (!isspace((unsigned char)*line))
			return (false);
		line++;
	}
	return (true);
}

int	print_err(char *info, char *str, int code)
{
	ft_putstr_fd("cub3D: Error", 2);
	if (info)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(info, 2);
	}
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putstr_fd("\n", 2);
	return (code);
}

void	free_mapping(char **str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		free(str[i]);
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	free_parser(t_parse *parse)
{
	if (parse->map != NULL)
		free_mapping(parse->map);
	if (parse->no_text != NULL)
		free(parse->no_text);
	if (parse->so_text != NULL)
		free(parse->so_text);
	if (parse->we_text != NULL)
		free(parse->we_text);
	if (parse->ea_text != NULL)
		free(parse->ea_text);
}
