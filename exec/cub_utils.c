/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:07:38 by rgarcia           #+#    #+#             */
/*   Updated: 2023/05/15 15:42:35 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_mapinfo	count_points_in_tab(char **tab)
{
	t_mapinfo	info;
	int			x;
	int			y;

	info.points = 0;
	info.size_y = 0;
	info.size_x = 0;
	y = 0;
	while (tab[y])
	{
		x = 0;
		while (tab[y][x] != '\0')
		{
			x++;
			info.points++;
		}
		if (x > info.size_x)
			info.size_x = x;
		y++;
	}
	info.size_y = y;
	return (info);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	iscubfile(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	while (i > 0 && file[i] != '.')
		i--;
	if (file[i] != '.')
		return (0);
	if (file[i + 1] != 'c')
		return (0);
	if (file[i + 2] != 'u')
		return (0);
	if (file[i + 3] != 'b')
		return (0);
	if (file[i + 4] != '\0')
		return (0);
	return (1);
}
