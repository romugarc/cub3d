#include "cub3d.h"

int	iscubfile(char *file)
{
	int	i;

	i = 0;
	while (file[i] != '.' && file[i] != '\0')
		i++;
	if (file[i] != '.')
		return (0);
	if (file[i + 1] != 'c')
		return (0);
	if (file[i + 2] != 'u')
		return (0);
	if (file[i + 3] != 'b')
		return (0);
	if (file[i + 4] != '\0')
		return (0);
	return (1);
}

int	error_handler(int argc, char **argv)
{
	if (argc != 2)
    {
        printf("Error: Only one argument allowed\n");
        return (0);
    }
	if (iscubfile(argv[1]) == 0)
	{
		printf("Error: Not .cub file\n");
        return (0);
	}
	return (1);
}

void	draw_sqr(t_map cmap, t_data img, t_mapinfo info)
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
}

void	draw_line(t_cam cam, t_data img, int x)
{
	int	y;
	int	big;
	int	color;

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
	while (y < big)
	{
		if (cam.side == 0)
			my_mlx_pixel_put(&img, x, y, color);
		else
			my_mlx_pixel_put(&img, x, y, color/2);
		y++;
	}
}

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
		//printf("ray%d\t%f\t%f\t%f\n", i, p->cam.camera_x, p->cam.raydir_x, p->cam.raydir_y);
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

void	drawing_map(t_params *p)
{
	//t_map		*cmap;
	//t_data		img;
	//t_mapinfo	info;
	//int			k;
	//int			offset;

	p->img.img = mlx_new_image(p->vmlx.mlx_ptr, p->vmlx.size_winx, p->vmlx.size_winy);
	p->img.addr = mlx_get_data_addr(p->img.img, &p->img.bits_per_pixel, &p->img.line_length, &p->img.endian);
	/*k = 0;
	while (k < info.points)
	{
		draw_sqr(cmap[k], img, info);
		k++;
	}*/
	raycast_lines(p);
	mlx_put_image_to_window(p->vmlx.mlx_ptr, p->vmlx.win_ptr, p->img.img, 0, 0);
	mlx_destroy_image(p->vmlx.mlx_ptr, p->img.img);
	//free(p->map);
}

void	translation(int keycode, t_params *prms)
{
	if (keycode == 123)
		prms->info.dir_x -= 0.1;
	else if (keycode == 124)
		prms->info.dir_x += 0.1;
	else if (keycode == 125)
		prms->info.dir_y += 0.1;
	else if (keycode == 126)
		prms->info.dir_y -= 0.1;
	//else if (keycode == 12)
	//	prms->vars.off_z += 0.01;
	//else if (keycode == 13)
	//	prms->vars.off_z -= 0.01;
}

int	key_hook(int keycode, t_params *prms)
{
	/*if (keycode != 60)
	{
		if ((keycode >= 123 && keycode <= 126)
			|| (keycode >= 12 && keycode <= 13))
			translation(keycode, prms);
		//else if (keycode == 0 || keycode == 1
		//	|| keycode == 14 || keycode == 15)
		//	zoom_and_rotation(keycode, prms);
		//else if (keycode == 53)
		//	close_window(prms);
		drawing_map(prms);
	}*/
	printf("aaaa\n");
	mlx_destroy_window(prms->vmlx.mlx_ptr, prms->vmlx.win_ptr);
	exit(0);
	return (0);
}

int main(int argc, char **argv)
{
	t_params	p;

    if (error_handler(argc, argv) == 0)
		return (0);
	p.v.fd = open(argv[1], O_RDONLY);
	init_vars(&p.vmlx, &p.v, argv[1]);
	p.vmlx.mlx_ptr = mlx_init();
	p.vmlx.win_ptr = mlx_new_window(p.vmlx.mlx_ptr, p.vmlx.size_winx, p.vmlx.size_winy, p.vmlx.title);
    parse_file(&p.v);
	if (init_all(&p) == 1)
		return (1);
	drawing_map(&p);
	mlx_hook(p.vmlx.win_ptr, 2, 0, key_hook, &p);
	mlx_loop(p.vmlx.mlx_ptr);
	free(p.vmlx.mlx_ptr);
	free(p.vmlx.win_ptr);
	ft_free_tab(p.v.map_data);
	close(p.v.fd);
    return (0);
}