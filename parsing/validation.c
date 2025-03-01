#include "../parsing.h"

void	validation_extantion(t_tinfo *mapp, int ac, char **av)
{
	char	*ptr;

	if (ac != 2)
		ft_error("argument", NULL);
	ptr = ft_strrchr(av[1], '.');
	if (ft_strncmp(av[1], ".cub", ft_strlen(".cub")) == 0)
		ft_error("Name your file 🐸\n", NULL);
	if (!ptr || ft_strncmp(ptr, ".cub", ft_strlen(ptr)))
		ft_error("extension. Must be .cub\n", NULL);
	// if you want to check on .cub.cub
	mapp->file_name = av[1];
}
void	validation_exist(t_tinfo *mapp)
{
	mapp->fd = open (mapp->file_name, O_RDONLY);
	if (mapp->fd < 0)
		ft_error("can not open this file", mapp->file_name);
}