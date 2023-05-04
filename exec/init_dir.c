/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:08:02 by rgarcia           #+#    #+#             */
/*   Updated: 2023/05/03 17:08:05 by rgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	init_dir2(char cardinal, t_mapinfo *info, t_cam *cam)
{
	if (cardinal == 'W')
	{
		info->dir_x = -1;
		info->dir_y = 0;
		cam->plane_x = 0;
		cam->plane_y = -0.66;
	}
	else if (cardinal == 'E')
	{
		info->dir_x = 1;
		info->dir_y = 0;
		cam->plane_x = 0;
		cam->plane_y = 0.66;
	}
}

void	init_dir(char cardinal, t_mapinfo *info, t_cam *cam)
{
	if (cardinal == 'N')
	{
		info->dir_x = 0;
		info->dir_y = -1;
		cam->plane_x = 0.66;
		cam->plane_y = 0;
	}
	else if (cardinal == 'S')
	{
		info->dir_x = 0;
		info->dir_y = 1;
		cam->plane_x = -0.66;
		cam->plane_y = 0;
	}
	else
		init_dir2(cardinal, info, cam);
}
