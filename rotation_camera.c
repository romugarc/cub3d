#include "cub3d.h"

void	rotation_camera(int keycode, t_params *p)
{
	double	swapdir_x;
	double	swapplane_x;
	double	angle;

	angle = p->cam.rad / 180 * M_PI;
	if (keycode == 65361)
	{
		swapdir_x = p->info.dir_x;
		p->info.dir_x = p->info.dir_x * cos(-angle) - p->info.dir_y * sin(-angle);
      	p->info.dir_y = swapdir_x * sin(-angle) + p->info.dir_y * cos(-angle);
		swapplane_x = p->cam.plane_x;
		p->cam.plane_x = p->cam.plane_x * cos(-angle) - p->cam.plane_y * sin(-angle);
      	p->cam.plane_y = swapplane_x * sin(-angle) + p->cam.plane_y * cos(-angle);
	}
	else if (keycode == 65363)
	{
		swapdir_x = p->info.dir_x;
		p->info.dir_x = p->info.dir_x * cos(angle) - p->info.dir_y * sin(angle);
      	p->info.dir_y = swapdir_x * sin(angle) + p->info.dir_y * cos(angle);
		swapplane_x = p->cam.plane_x;
		p->cam.plane_x = p->cam.plane_x * cos(angle) - p->cam.plane_y * sin(angle);
      	p->cam.plane_y = swapplane_x * sin(angle) + p->cam.plane_y * cos(angle);
	}
	//else if (keycode == 12)
	//	prms->vars.off_z += 0.01;
	//else if (keycode == 13)
	//	prms->vars.off_z -= 0.01;
}