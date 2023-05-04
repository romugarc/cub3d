/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:08:45 by rgarcia           #+#    #+#             */
/*   Updated: 2023/05/03 17:08:46 by rgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotation_camera2(int keycode, t_params *p)
{
	double	swapdir_x;
	double	swapplane_x;
	double	angle;

	angle = p->cam.rad / 180 * M_PI;
	if (keycode == 65363)
	{
		swapdir_x = p->info.dir_x;
		p->info.dir_x = p->info.dir_x * cos(angle) - p->info.dir_y * sin(angle);
		p->info.dir_y = swapdir_x * sin(angle) + p->info.dir_y * cos(angle);
		swapplane_x = p->cam.plane_x;
		p->cam.plane_x = \
			p->cam.plane_x * cos(angle) - p->cam.plane_y * sin(angle);
		p->cam.plane_y = swapplane_x * sin(angle) + p->cam.plane_y * cos(angle);
	}
}

void	rotation_camera(int keycode, t_params *p)
{
	double	swapdir_x;
	double	swapplane_x;
	double	angle;

	angle = p->cam.rad / 180 * M_PI;
	if (keycode == 65361)
	{
		swapdir_x = p->info.dir_x;
		p->info.dir_x = \
			p->info.dir_x * cos(-angle) - p->info.dir_y * sin(-angle);
		p->info.dir_y = swapdir_x * sin(-angle) + p->info.dir_y * cos(-angle);
		swapplane_x = p->cam.plane_x;
		p->cam.plane_x = \
			p->cam.plane_x * cos(-angle) - p->cam.plane_y * sin(-angle);
		p->cam.plane_y = \
			swapplane_x * sin(-angle) + p->cam.plane_y * cos(-angle);
	}
}
