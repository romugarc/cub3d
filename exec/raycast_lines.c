/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:08:17 by rgarcia           #+#    #+#             */
/*   Updated: 2023/05/03 17:08:19 by rgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	get_raydir(t_params *p, int i)
{
	p->cam.camera_x = 2 * i / (double)p->vmlx.size_winx - 1;
	p->cam.raydir_x = p->info.dir_x + p->cam.plane_x * p->cam.camera_x;
	p->cam.raydir_y = p->info.dir_y + p->cam.plane_y * p->cam.camera_x;
	if (p->cam.raydir_x == 0)
		p->cam.deltadist_x = 100000;
	else
	{
		p->cam.deltadist_x = 1 / p->cam.raydir_x;
		if (p->cam.deltadist_x < 0)
			p->cam.deltadist_x = -p->cam.deltadist_x;
	}
	if (p->cam.raydir_y == 0)
		p->cam.deltadist_y = 100000;
	else
	{
		p->cam.deltadist_y = 1 / p->cam.raydir_y;
		if (p->cam.deltadist_y < 0)
			p->cam.deltadist_y = -p->cam.deltadist_y;
	}
}

static void	get_sidedist(t_params *p)
{
	if (p->cam.raydir_x < 0)
	{
		p->cam.step_x = -1;
		p->cam.sidedist_x = \
			(p->info.start_x - p->info.map_x) * p->cam.deltadist_x;
	}
	else
	{
		p->cam.step_x = 1;
		p->cam.sidedist_x = \
			(p->info.map_x + 1.0 - p->info.start_x) * p->cam.deltadist_x;
	}
	if (p->cam.raydir_y < 0)
	{
		p->cam.step_y = -1;
		p->cam.sidedist_y = \
			(p->info.start_y - p->info.map_y) * p->cam.deltadist_y;
	}
	else
	{
		p->cam.step_y = 1;
		p->cam.sidedist_y = \
			(p->info.map_y + 1.0 - p->info.start_y) * p->cam.deltadist_y;
	}
}

static void	get_sidehit(t_params *p)
{
	if (p->cam.sidedist_x < p->cam.sidedist_y)
	{
		p->cam.sidedist_x += p->cam.deltadist_x;
		p->info.map_x += p->cam.step_x;
		if (p->cam.step_x == 1)
			p->cam.side = 0;
		else
			p->cam.side = 2;
	}
	else
	{
		p->cam.sidedist_y += p->cam.deltadist_y;
		p->info.map_y += p->cam.step_y;
		if (p->cam.step_y == 1)
			p->cam.side = 1;
		else
			p->cam.side = 3;
	}
	if (p->info.map_y < 0 || p->info.map_y >= p->info.size_y)
		p->cam.hit = 1;
	else if (p->info.map_x < 0 || p->info.map_x > p->info.size_x)
		p->cam.hit = 1;
	else if (p->v.map_data[p->info.map_y][p->info.map_x] == '1')
		p->cam.hit = 1;
}

static void	get_perplinedraw(t_params *p)
{
	if (p->cam.side == 0 || p->cam.side == 2)
		p->cam.perpwalldist = p->cam.sidedist_x - p->cam.deltadist_x;
	else
		p->cam.perpwalldist = p->cam.sidedist_y - p->cam.deltadist_y;
	p->cam.lineheight = (int)(p->vmlx.size_winy / p->cam.perpwalldist);
	p->cam.draw_start = (-p->cam.lineheight / 2) + (p->vmlx.size_winy / 2);
	p->cam.draw_end = (p->cam.lineheight / 2) + (p->vmlx.size_winy / 2);
	if (p->cam.draw_start < 0)
		p->cam.draw_start = 0;
	else if (p->cam.draw_start >= p->vmlx.size_winy)
		p->cam.draw_start = p->vmlx.size_winy - 1;
	if (p->cam.draw_end < 0)
		p->cam.draw_end = 0;
	else if (p->cam.draw_end >= p->vmlx.size_winy)
		p->cam.draw_end = p->vmlx.size_winy - 1;
}

void	raycast_lines(t_params *p)
{
	int	i;

	i = 0;
	while (i < p->vmlx.size_winx)
	{
		p->info.map_x = (int)p->info.start_x;
		p->info.map_y = (int)p->info.start_y;
		get_raydir(p, i);
		get_sidedist(p);
		p->cam.hit = 0;
		while (p->cam.hit == 0)
			get_sidehit(p);
		get_perplinedraw(p);
		p->tex[p->cam.side].tex_x = \
			get_tex_x(p->cam, p->info, p->tex[p->cam.side]);
		draw_line(*p, i, p->vmlx.size_winy);
		i++;
	}
}
