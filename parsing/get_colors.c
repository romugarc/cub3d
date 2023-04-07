/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warnora <warnora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:22:30 by warnora           #+#    #+#             */
/*   Updated: 2023/02/27 19:36:06 by warnora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	atoiv2(char *str, int *i)
{
	int	nb;

	nb = 0;
	while (str[(*i)] && str[(*i)] != ',')
	{
		nb = (nb * 10) + (str[(*i)] - '0');
		(*i) = (*i) + 1;
	}
	if (str[(*i)])
		(*i) = (*i) + 1;
	return (nb);
}

void	get_colors(t_vars *vars)
{
	int	i;

	i = 0;
	vars->color_floor = 0x00 + ((atoiv2(vars->floor, &i) * 256) * 256);
	vars->color_floor = vars->color_floor + (atoiv2(vars->floor, &i) * 256);
	vars->color_floor = vars->color_floor + atoiv2(vars->floor, &i);
	i = 0;
	vars->color_ceiling = 0x00 + (((atoiv2(vars->ceiling, &i) * 256) * 256));
	vars->color_ceiling = vars->color_ceiling + (atoiv2(vars->ceiling, &i) * 256);
	vars->color_ceiling = vars->color_ceiling + atoiv2(vars->ceiling, &i);
	printf("%x -- %x\n\n", vars->color_floor, vars->color_ceiling);
}