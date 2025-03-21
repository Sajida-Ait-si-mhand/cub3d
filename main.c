#include "include/main.h"
int validation_extantion(t_parse *mapp, int ac, char **av)
{
    char *ptr;

    if (ac != 2)
        ft_error("Incorrect number of arguments!", NULL);
    
    ptr = ft_strrchr(av[1], '.');
    if (!ptr)
        ft_error("Missing file extension (.cub)!", NULL);
    
    if (ft_strncmp(ptr, ".cub", ft_strlen(".cub") + 1) != 0)
        ft_error("Invalid extension! Must be .cub", NULL);
    
    mapp->fd = open(av[1], O_RDONLY);
    if (mapp->fd < 0)
        ft_error("Failed to open file!", NULL);
    
    mapp->file_name = av[1];
    return (1);
}

int main(int ac, char **av)
{
    t_parse parse; 

    ft_memset(&parse, 0, sizeof(t_parse));
    parse.floor_color = -1;
    parse.ceil_color = -1;
    parse.valid_set = "01NEWS";

    validation_extantion(&parse, ac, av);
    if (ft_parse(&parse))
        return (free_parser(&parse), EXIT_FAILURE);
    return (0);
}
