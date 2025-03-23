/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_color.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 02:39:25 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/23 11:53:52 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

static int	validate_line_for_spaces(const char *line)
{
	int	found_digit;

	found_digit = 0;
	while (*line)
	{
		if (isdigit(*line))
		{
			found_digit = 1;
		}
		else if (*line == ' ' || *line == '\t')
		{
			if (found_digit && isdigit(*(line + 1)))
			{
				return (1);
			}
		}
		else
		{
			found_digit = 0;
		}
		line++;
	}
	return (0);
}

static int	clean_space_around_comma(char *line, char *ptr)
{
	char	*temp;
	int		shift;
	shift = 0;
	if (*ptr == ',')
	{
		if (ptr > line && (*(ptr - 1) == ' ' || *(ptr - 1) == '\t'))
		{
			temp = ptr - 1;
			while (*temp++)
				*temp = *(temp + 1);
			ptr--;
			shift = 1;
		}
		if (*(ptr + 1) == ' ' || *(ptr + 1) == '\t')
		{
			temp = ptr + 1;
			while (*temp++)
				*temp = *(temp + 1);
		}
	}
	return (shift);
}

static void	clean_line(char *line)
{
	char	*ptr;
	char	*temp;
	int		shift;

	ptr = line;
	while (*ptr)
	{
		if (*ptr == ' ' || *ptr == '\t')
		{
			temp = ptr;
			while (*temp)
			{
				*temp = *(temp + 1);
				temp++;
			}
			continue ;
		}
		shift = clean_space_around_comma(line, ptr);
		if (shift)
			continue ;
		ptr++;
	}
}

int	ft_ceil(t_parse *parse, char *line)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	r = 0;
	g = 0;
	b = 0;
	from_new_line_to_ziroo(line);
	if (validate_line_for_spaces(line))
		return (ft_error("🚨 INVALID RGB FORMAT! ", line), 1);
	clean_line(line);
	split = ft_split(line, ',');
	if (!split || !split[0] || !split[1] || !split[2])
	{
		return (ft_error("🚨 INVALID COLOR IDENTIFIER!", line), 1);
	}
	if (split[3])
		return (ft_error("🚨 INVALID RGB FORMAT! Too many components", line), 1);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_mapping(split);
	printf("Ceil color: %d, %d, %d\n", r, g, b);
	ft_check_rgb_c(parse, r, g, b);
	return (0);
}
