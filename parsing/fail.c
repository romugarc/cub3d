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

static void	free_map(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->map_data)
	{
		while (vars->map_data[i])
		{
			free(vars->map_data[i]);
			i++;
		}
	}
	if (vars->map_data)
		free(vars->map_data);
}

void	fail(char *str, t_vars *vars)
{
	if (vars->north)
		free(vars->north);
	if (vars->south)
		free(vars->south);
	if (vars->east)
		free(vars->east);
	if (vars->west)
		free(vars->west);
	if (vars->floor)
		free(vars->floor);
	if (vars->ceiling)
		free(vars->ceiling);
	if (vars->map_in_str)
		free(vars->map_in_str);
	if (vars->gnl_ret)
		free(vars->gnl_ret);
	free_map(vars);
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}
