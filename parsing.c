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

#include "cub3d.h"

void	parse_file(t_vars *vars)
{
	char	*data;
	int		len;
	int		i;

	i = 0;
	data = NULL;
	vars->gnl_ret = "a";
	while (vars->gnl_ret)
	{
		len = 1;
		vars->gnl_ret = get_next_line(vars->fd);
		if (vars->gnl_ret != NULL)
		{
			len = ft_strlen(vars->gnl_ret);
			i++;
		}
		data = ft_strjoin_to_i(data, vars->gnl_ret, len);
		free(vars->gnl_ret);
	}
	vars->map_data = ft_split(data, '\n');
}

