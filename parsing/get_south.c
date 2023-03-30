/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_south.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warnora <warnora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:22:30 by warnora           #+#    #+#             */
/*   Updated: 2023/02/27 19:36:06 by warnora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	get_south_next(t_vars *vars, int *i, int *j)
{
	vars->south[(*j)] = vars->gnl_ret[(*i)];
	(*i) = (*i) + 1;
	(*j) = (*j) + 1;
}

void	get_south(t_vars *vars, int i)
{
	int	j;

	j = 0;
	i++;
	if (vars->gnl_ret[i] == 'O')
		i++;
	else
		fail("Error\nBad format for south\n");
	i++;
	while (vars->gnl_ret[i] == ' ')
		i++;
	if (vars->gnl_ret[i] == '\0')
		fail("Error\nMissing path for south\n");
	vars->south = malloc(sizeof(char) * (strlen_itoc(vars->gnl_ret, i, '\0') + 1));
	if (!vars->south)
		fail("Malloc error !");
	while (vars->gnl_ret[i] && vars->gnl_ret[i] != '\n')
		get_south_next(vars, &i, &j);
	vars->south[j] = '\0';
	j = open(vars->south, O_RDONLY);
	if (j == -1)
		fail("Error\nBad path fot south\n");
	close(j);
}