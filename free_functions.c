#include "cub3d.h"

void	ft_free_tab(char **tab)
{
	int	i;

	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
}