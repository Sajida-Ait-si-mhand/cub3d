/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ziyada.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejd <ael-mejd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 02:40:28 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/24 01:30:18 by ael-mejd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\r' || c == '\b');
}

int	ft_error(t_parse *parse, char *str, char *arg)
{
	free_parser(&parse);
	(void)arg;
	printf("\033[0;31m Error: %s \033[0m", str);
	return (1);
}

void	ft_check_rgb_c(t_parse *parse, int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_error(parse, "🚨 RGB values must be between 0 and 255", NULL);
		return ;
	}
	parse->ceil_color = (r << 16) | (g << 8) | b;
}

void	ft_check_rgb_f(t_parse *parse, int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_error(parse, "🚨 RGB values must be between 0 and 255", NULL);
		return ;
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
