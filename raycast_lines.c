#include "cub3d.h"

void	raycast_lines(t_params *p)
{
	int	i;

	i = 0;
	while (i < p->vmlx.size_winx)
	{
		p->info.map_x = (int)p->info.start_x;
		p->info.map_y = (int)p->info.start_y;
		p->cam.camera_x = 2 * i / (double)p->vmlx.size_winx - 1;
		p->cam.raydir_x = p->info.dir_x + p->cam.plane_x * p->cam.camera_x;
		p->cam.raydir_y = p->info.dir_y + p->cam.plane_y * p->cam.camera_x;
		//printf("ray%d\t%f\t%f\t%f\t%f\t%f\n", i, p->cam.camera_x, p->info.dir_x, p->cam.raydir_x, p->info.dir_y, p->cam.raydir_y);
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
		//printf("delta%d\t%f\t%f\n", i, p->cam.deltadist_x, p->cam.deltadist_y);
		if (p->cam.raydir_x < 0)
		{
			p->cam.step_x = -1;
			p->cam.sidedist_x = (p->info.start_x - p->info.map_x) * p->cam.deltadist_x;
		}
		else
		{
			p->cam.step_x = 1;
			p->cam.sidedist_x = (p->info.map_x + 1.0 - p->info.start_x) * p->cam.deltadist_x;
		}
		if (p->cam.raydir_y < 0)
		{
			p->cam.step_y = -1;
			p->cam.sidedist_y = (p->info.start_y - p->info.map_y) * p->cam.deltadist_y;
		}
		else
		{
			p->cam.step_y = 1;
			p->cam.sidedist_y = (p->info.map_y + 1.0 - p->info.start_y) * p->cam.deltadist_y;
		}
		//printf("sidedist%d\t%f\t%f\n", i, p->cam.sidedist_x, p->cam.sidedist_y);
		p->cam.hit = 0;
		while (p->cam.hit == 0)
		{
			//printf("%f\t%f\n", p->cam.sidedist_x, p->cam.sidedist_y);
			if (p->cam.sidedist_x < p->cam.sidedist_y)
			{
				p->cam.sidedist_x += p->cam.deltadist_x;
				p->info.map_x += p->cam.step_x;
				//check les valeurs absolues dir_x et dir_y avant de décider du side
				p->cam.side = 0;
			}
			else
			{
				p->cam.sidedist_y += p->cam.deltadist_y;
				p->info.map_y += p->cam.step_y;
				p->cam.side = 1;
			}
			//printf("%d\t%d\n", p->info.map_x, p->info.map_y);
			if (p->v.map_data[p->info.map_y][p->info.map_x] == '1')
				p->cam.hit = 1;
		}
		//printf("side%d\n", p->cam.side);
		if (p->cam.side == 0)
			p->cam.perpwalldist = p->cam.sidedist_x - p->cam.deltadist_x;
		else
			p->cam.perpwalldist = p->cam.sidedist_y - p->cam.deltadist_y;
		p->cam.lineheight = (int)(p->vmlx.size_winy / p->cam.perpwalldist);
		//printf("%d\t%f\n", p->cam.lineheight, p->cam.perpwalldist);
		p->cam.draw_start = (-p->cam.lineheight / 2) + (p->vmlx.size_winy / 2);
		p->cam.draw_end = (p->cam.lineheight / 2) + (p->vmlx.size_winy / 2);
		//printf("%d\t%d\t%d\n", i, p->cam.draw_start, p->cam.draw_end);
		if (p->cam.draw_start < 0)
			p->cam.draw_start = 0;
		else if (p->cam.draw_start >= p->vmlx.size_winy)
			p->cam.draw_start = p->vmlx.size_winy - 1;
		if (p->cam.draw_end < 0)
			p->cam.draw_end = 0;
		else if (p->cam.draw_end >= p->vmlx.size_winy)
			p->cam.draw_end = p->vmlx.size_winy - 1;
		//printf("%d\t%d\t%d\n", i, p->cam.draw_start, p->cam.draw_end);
		draw_line(p->cam, p->img, i);
		i++;
	}
}