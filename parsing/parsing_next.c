/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warnora <warnora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:22:30 by warnora           #+#    #+#             */
/*   Updated: 2023/02/27 19:36:06 by warnora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	strlen_itoc(char *str, int i, char c)
{
	int	size;

	size = 0;
	while (str[i] && str[i] != c)
	{	
		size++;
		i++;
	}
	return (size);
}

int	map_char(char c)
{
	if (c == '1' || c == '0')
		return (TRUE);
	return (FALSE);
}

int	check_path_and_colors(t_vars *vars)
{
	if (!(vars->north && vars->south && vars->east && vars->west
		&& vars->floor && vars->ceiling))
			return (FALSE);
	return (TRUE);
}
