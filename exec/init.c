/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:09:02 by rgarcia           #+#    #+#             */
/*   Updated: 2023/05/03 17:09:03 by rgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_vars(t_varmlx *varmlx, t_vars *vars, char *file)
{
	varmlx->title = file;
	varmlx->size_winx = 500;
	varmlx->size_winy = 500;
	vars->fd = open(file, O_RDONLY);
	vars->north = NULL;
	vars->south = NULL;
	vars->east = NULL;
	vars->west = NULL;
	vars->floor = NULL;
	vars->ceiling = NULL;
	vars->gnl_ret = NULL;
	vars->map_data = NULL;
	vars->map_in_str = NULL;
}

t_map	*init_map(char **parsed_data, t_mapinfo info)
{
	t_map	*map;
	int		i;
	int		j;
	int		k;

	map = malloc(sizeof(t_map) * (info.points) + 1);
	if (!map)
		return (0);
	i = 0;
	k = 0;
	while (parsed_data[i])
	{
		j = 0;
		while (parsed_data[i][j])
		{
			map[k].x = j;
			map[k].y = i;
			map[k].type = parsed_data[i][j];
			j++;
			k++;
		}
		i++;
	}
	return (map);
}

int	init_playerpos(t_map *cmap, t_mapinfo *info, t_cam *cam)
{
	int	k;

	k = 0;
	while (k < info->points)
	{
		if (cmap[k].type == 'N' || cmap[k].type == 'S'
			|| cmap[k].type == 'W' || cmap[k].type == 'E')
		{
			info->start_x = (double)cmap[k].x;
			info->start_y = (double)cmap[k].y;
			info->map_x = cmap[k].x;
			info->map_y = cmap[k].y;
			init_dir(cmap[k].type, info, cam);
			return (1);
		}
		k++;
	}
	return (0);
}

void	init_cam(t_params *p)
{
	p->cam.hit = 0;
	p->cam.rad = 9;
	p->cam.movespeed = 1;
}

int	init_all(t_params *p)
{
	p->info = count_points_in_tab(p->v.map_data);
	p->map = init_map(p->v.map_data, p->info);
	if (!p->map)
	{
		free(p->tex);
		return (1);
	}
	init_playerpos(p->map, &p->info, &p->cam);
	init_cam(p);
	return (0);
}
