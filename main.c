/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 03:13:51 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/24 02:05:08 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

int	validation_extantion(t_parse *mapp, int ac, char **av)
{
	char	*ptr;

	if (ac != 2)
		return (ft_error(mapp, "Incorrect number of arguments!", NULL));
	ptr = ft_strrchr(av[1], '.');
	if (!ptr)
		return (ft_error(mapp, "Missing file extension (.cub)!", NULL));
	if (ft_strncmp(ptr, ".cub", ft_strlen(".cub") + 1) != 0)
		return (ft_error(mapp, "Invalid extension! Must be .cub", NULL));
	mapp->fd = open(av[1], O_RDONLY);
	if (mapp->fd < 0)
		return (ft_error(mapp, "Failed to open file!", NULL));
	mapp->file_name = av[1];
	return (1);
}

int	main(int ac, char **av)
{
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	if (!parse)
		return (EXIT_FAILURE);
	ft_memset(parse, 0, sizeof(t_parse));
	parse->floor_color = -1;
	parse->ceil_color = -1;
	parse->valid_set = "01NEWS";
	validation_extantion(parse, ac, av);
	if (ft_parse(parse))
		return (free_parser(&parse), EXIT_FAILURE);
	merge(parse);
	return (0);
}
