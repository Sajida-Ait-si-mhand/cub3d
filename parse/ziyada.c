/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ziyada.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 02:40:28 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/23 05:17:24 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

int	ft_isspace(int c)
{
	return (c == ' '  || c == '\r' || c == '\b');
}

void	ft_error(char *str, char *arg)
{
	printf("\033[0;31m Error: %s \033[0m", str);
	if (arg)
		printf(":\033[38;5;121m %s \033[0m", arg);
	exit(1);
}

void	ft_check_rgb_c(t_parse *parse, int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_error("🚨 RGB values must be between 0 and 255", NULL);
	}
	parse->ceil_color = (r << 16) | (g << 8) | b;
}

void	ft_check_rgb_f(t_parse *parse, int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_error("🚨 RGB values must be between 0 and 255", NULL);
	}
	parse->floor_color = (r << 16) | (g << 8) | b;
}

void	from_new_line_to_ziroo(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
	}
}
