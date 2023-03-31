#include "cub3d.h"

/*void	draw_sqr(t_map cmap, t_data img, t_mapinfo info)
{
	int	i;
	int	j;
	int	chunkl;
	
	if (info.chunk_x > info.chunk_y)
		chunkl = info.chunk_y;
	else
		chunkl = info.chunk_x;
	if (cmap.type == '1')
	{
		i = 0;
		while (i++ < chunkl)
		{
			j = 0;
			while (j++ < chunkl)
				my_mlx_pixel_put(&img, cmap.x * chunkl + i, cmap.y * chunkl + j, 0x00FFFFFF);
		}
	}
	else if (cmap.type == 'N')
	{
		i = 0;
		while (i++ < chunkl)
		{
			j = 0;
			while (j++ < chunkl)
				my_mlx_pixel_put(&img, cmap.x * chunkl + i, cmap.y * chunkl + j, 0x0000FF00);
		}
	}
}*/

int	error_handler(int argc, char **argv)
{
	if (argc != 2)
		fail("Error\nOnly one argument allowed\n");
	if (iscubfile(argv[1]) == 0)
		fail("Error\nNot .cub file\n");
	return (1);
}

int main(int argc, char **argv)
{
	t_params	p;

    if (error_handler(argc, argv) == 0)
		return (0);
	//p.v.fd = open(argv[1], O_RDONLY);
	init_vars(&p.vmlx, &p.v, argv[1]);
	parse_file(&p.v);
	p.vmlx.mlx_ptr = mlx_init();
	p.vmlx.win_ptr = mlx_new_window(p.vmlx.mlx_ptr, p.vmlx.size_winx, p.vmlx.size_winy, p.vmlx.title);
	if (init_all(&p) == 1)
		return (1);
	drawing_map(&p);
	mlx_hook(p.vmlx.win_ptr, 2, 1L<<0, key_hook, &p);
	mlx_hook(p.vmlx.win_ptr, 17, 1L<<0, close_window, &p);
	mlx_loop(p.vmlx.mlx_ptr);
    return (0);
}