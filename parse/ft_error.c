/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 02:39:50 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/24 02:03:57 by saait-si         ###   ########.fr       */
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

void	free_parser(t_parse **parse)
{
	int	i;

	if (!parse || !*parse)
		return ;
	if ((*parse)->map)
		free_mapping((*parse)->map);
	i = 0;
	while (i < 4)
	{
		if ((*parse)->tex_path[i])
			free((*parse)->tex_path[i]);
		i++;
	}
	free(*parse);
	*parse = NULL;
	exit(1);
}
