#include "../cub3d.h"

void	floor_cast(t_params	*p)
{
	int	y;
	int	x;

	y = 0;
	while (y < p->vmlx.size_winy / 2)
	{
		x = 0;
		while (x < p->vmlx.size_winx)
		{
			my_mlx_pixel_put(&p->img, x, y, p->v.color_ceiling);
			x++;
		}
		y++;
	}
	while (y < p->vmlx.size_winy)
	{
		x = 0;
		while (x < p->vmlx.size_winx)
		{
			my_mlx_pixel_put(&p->img, x, y, p->v.color_floor);
			x++;
		}
		y++;
	}
}
