#include "cub3d.h"

void	init_vars(t_varmlx *varmlx, t_vars *vars, char *file)
{
	varmlx->title = file;
	varmlx->size_winx = 1000;
	varmlx->size_winy = 500;
	vars->fd = open(file, O_RDONLY);
	vars->north = NULL;
	vars->south = NULL;
	vars->east = NULL;
	vars->west = NULL;
	vars->floor = NULL;
	vars->ceiling = NULL;
	vars->map_in_str = NULL;
}

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
		fail("Error\nOnly one argument allowed\n");
	if (iscubfile(argv[1]) == 0)
		fail("Error\nNot .cub file\n");
	return (1);
}

t_mapinfo	count_points_in_tab(char **tab)
{
	t_mapinfo	info;
	int	x;
	int	y;

	info.points = 0;
	info.size_y = 0;
	info.size_x = 0;
	y = 0;
	while (tab[y])
	{
		x = 0;
		while (tab[y][x] != '\0')
		{
			x++;
			info.points++;
		}
		if (x > info.size_x)
			info.size_x = x;
		y++;
	}
	info.size_y = y;
	return (info);
}

t_map	*ft_generate_map(char **parsed_data, t_mapinfo *info)
{
	t_map	*map;
	int		i;
	int		j;
	int		k;

	*info = count_points_in_tab(parsed_data);
	map = malloc(sizeof(t_map) * (info->points) + 1);
	if (!map)
		return (0);
	i = 0;
	k = 0;
	while (parsed_data[i])
	{
		j = 0;
		while (parsed_data[i][j])
		{
			map[k].x = j;
			map[k].y = i;
			map[k].type = parsed_data[i][j];
			j++;
			k++;
		}
		i++;
	}
	return (map);
}

void	draw_sqr(t_map cmap, t_data img, t_mapinfo info)
{
	int	i;
	int	j;

	if (cmap.type == '1')
	{
		i = 0;
		while (i++ < info.chunk_x)
		{
			j = 0;
			while (j++ < info.chunk_y)
				my_mlx_pixel_put(&img, cmap.x * info.chunk_x + i, cmap.y * info.chunk_y + j, 0x00FFFFFF);
		}
	}
}

// void	drawing_map(t_vars *vars, t_varmlx *v)
// {
// 	t_map		*cmap;
// 	t_data		img;
// 	t_mapinfo	info;
// 	int			k;
// 	// int			offset;

// 	img.img = mlx_new_image(v->mlx_ptr, v->size_winx, v->size_winy);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
// 	cmap = ft_generate_map(vars->map_data, &info);
// 	info.chunk_x = v->size_winx / info.size_x;
// 	info.chunk_y = v->size_winy / info.size_y;
// 	k = 0;
// 	// offset = 0;
// 	while (k < info.points)
// 	{
// 		draw_sqr(cmap[k], img, info);
// //		if (cmap[k].type == '1')
// //			my_mlx_pixel_put(&img, cmap[k].x, cmap[k].y, 0x00FFFFFF);
// 		k++;
// 	}
// 	mlx_put_image_to_window(v->mlx_ptr, v->win_ptr, img.img, 0, 0);
// 	mlx_destroy_image(v->mlx_ptr, img.img);
// 	free(cmap);
// }

int main(int argc, char **argv)
{
	t_varmlx	v;
	t_vars		vars;

    if (error_handler(argc, argv) == 0)
		return (0);
	// vars.fd = open(argv[1], O_RDONLY); 2 X open ??
	init_vars(&v, &vars, argv[1]);
    parse_file(&vars);
	v.mlx_ptr = mlx_init();
	v.win_ptr = mlx_new_window(v.mlx_ptr, v.size_winx, v.size_winy, v.title);
	// drawing_map(&vars, &v);
	// mlx_loop(v.mlx_ptr);
	free(v.mlx_ptr);
	free(v.win_ptr);
	close(vars.fd);
	exit(EXIT_SUCCESS);
    return (0);
}