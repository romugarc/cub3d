/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_east.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warnora <warnora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:22:30 by warnora           #+#    #+#             */
/*   Updated: 2023/02/27 19:36:06 by warnora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_path(t_vars *vars, int *i, int *j)
{
		vars->east[(*j)] = vars->gnl_ret[(*i)];
		(*i) = (*i) + 1;
		(*j) = (*j) + 1;
}

void	get_east(t_vars *vars, int i)
{
	int	j;

	j = 0;
	i++;
	if (vars->gnl_ret[i] == 'A')
		i++;
	else
		fail("Error\nBad format for east\n");
	i++;
	while (vars->gnl_ret[i] == ' ')
		i++;
	if (vars->gnl_ret[i] == '\0')
		fail("Error\nMissing path for east\n");
	vars->east = malloc(sizeof(char) * (strlen_itoc(vars->gnl_ret, i, '\0') + 1));
	if (!vars->east)
		fail("Malloc error !");
	while (vars->gnl_ret[i] && vars->gnl_ret[i] != '\n')
		check_path(vars, &i, &j);
	vars->east[j] = '\0';
	j = open(vars->east, O_RDONLY);
	if (j == -1)
		fail("Error\nBad path for east\n");
	close(j);
}