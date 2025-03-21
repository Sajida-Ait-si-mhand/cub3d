#include "../include/main.h"


bool check_f_and_last_line(char **map, int height)
{
	int i;
	int f;

	i = 0;
	f = 0;
	while (map[0][f])
	{
		if (map[0][f] != '1' && map[0][f] != 32 && map[0][f] != '\n')
			return (ft_error("👾 YOU NEED '1' IN FIRST ROW 👾", map[0]), false);
		f++;
	}
	f = 0;
	while (map[height - 1][f])
	{
		if (map[height - 1][f] != '1' && map[height - 1][f] != 32 && map[height - 1][f] != '\n')
			return(ft_error("👾 YOU NEED '1' IN LAST ROW 👾", map[height - 1]), false);
		f++;
	}
	return (true);
}
bool ft_check_map_spaces_above_zero(t_parse *parse, char **map)
{
    int i;
    int j;

    // Start from the second row (index 1) because the first row has no row above it
    for (i = 1; i < parse->map_height; i++)
    {
        for (j = 0; map[i][j]; j++)
        {
            // Check if the current character is '0'
            if (map[i][j] == '0')
            {
                // Check if the character directly above is a space
                if (map[i - 1][j] == ' ')
                    return (ft_error("MAP ERROR: Space above '0' detected!", map[i]), false);
            }
        }
    }
    return (true);
}

bool	validate_map(t_parse *parse)
{
	char	**copy;

	copy = duplicate_map(parse,parse->map, &parse->map_height);
	if (!copy)
		return (false);
	if (parse->map_height < 3)
		return (false);
	if (!ft_check_map_borders(parse, copy))
		return (free_mapping(copy), false);
	if (!check_f_and_last_line(copy, parse->map_height))
		return (free_mapping(copy), false);
	if (!check_player(parse))
		return (free_mapping(copy), false);
	// if (!ft_check_map_spaces_above_zero(parse, parse->map))
   	// 	return (false);
	calculate_map_width(parse, copy);
	return (free_mapping(copy), true);
}

int	validate_and_close(t_parse *parse)
{
	if (!validate_map(parse))
	{
		close(parse->fd);
		return (print_err(NULL, "Invalid map", 1));
	}
	if (parse->texture_count != 4 || parse->floor_color == -1
		|| parse->ceil_color == -1)
	{
		close(parse->fd);
		return (print_err(NULL, "Missing required configurations", 1));
	}
	return (close(parse->fd), 0);
}