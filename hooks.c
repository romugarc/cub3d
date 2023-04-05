#include "cub3d.h"

int	close_window(t_params *prms)
{
	mlx_destroy_window(prms->vmlx.mlx_ptr, prms->vmlx.win_ptr);
	free(prms->vmlx.mlx_ptr);
	ft_free_tab(prms->v.map_data);
	free(prms->v.north);
	free(prms->v.west);
	free(prms->v.east);
	free(prms->v.south);
	free(prms->v.floor);
	free(prms->v.ceiling);
	free(prms->map);
	close(prms->v.fd);
	exit(0);
}

int	key_hook(int keycode, t_params *prms)
{
	if (keycode == 65307)
		close_window(prms);
	if ((keycode >= 65361 && keycode <= 65364))
		rotation_camera(keycode, prms);
	else if (keycode == 119 || keycode == 97
		|| keycode == 115 || keycode == 100)
		movement(keycode, prms);
	drawing_map(prms);
	return (0);
}