#include "cub3d.h"

void	draw_line(t_cam cam, t_data img, int x)
{
	int	y;
	int	big;
	int	color;
	int	green;

	if (cam.draw_start <= cam.draw_end)
	{
		y = cam.draw_start;
		big = cam.draw_end;
	}
	else
	{
		y = cam.draw_end;
		big = cam.draw_start;
	}
	color = 0x0000FFFF;
	green = 0x00FF0000;
	while (y < big)
	{
		if (cam.side == 0)
			my_mlx_pixel_put(&img, x, y, color);
		else if (cam.side == 1)
			my_mlx_pixel_put(&img, x, y, color/2);
		else if (cam.side == 2)
			my_mlx_pixel_put(&img, x, y, green);
		else if (cam.side == 3)
			my_mlx_pixel_put(&img, x, y, green/2);
		y++;
	}
}

void	drawing_map(t_params *p)
{
	p->img.img = mlx_new_image(p->vmlx.mlx_ptr, p->vmlx.size_winx, p->vmlx.size_winy);
	p->img.addr = mlx_get_data_addr(p->img.img, &p->img.bits_per_pixel, &p->img.line_length, &p->img.endian);
	raycast_lines(p);
	mlx_put_image_to_window(p->vmlx.mlx_ptr, p->vmlx.win_ptr, p->img.img, 0, 0);
	mlx_destroy_image(p->vmlx.mlx_ptr, p->img.img);
}