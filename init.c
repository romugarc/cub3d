#include "cub3d.h"

void	init_vars(t_varmlx *varmlx, t_vars *vars, char *file)
{
	varmlx->title = file;
	varmlx->size_winx = 500;
	varmlx->size_winy = 500;
	vars->fd = open(file, O_RDONLY);
}

t_map	*init_map(char **parsed_data, t_mapinfo info)
{
	t_map	*map;
	int		i;
	int		j;
	int		k;

	map = malloc(sizeof(t_map) * (info.points) + 1);
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

void	init_playerpos(t_map *cmap, t_mapinfo *info)
{
	int	k;

	k = 0;
	while (k < info->points)
	{
		if (cmap[k].type == 'N')
		{
			info->start_x = (double)cmap[k].x;
			info->start_y = (double)cmap[k].y;
			info->map_x = cmap[k].x;
			info->map_y = cmap[k].y;
			info->dir_x = -1;
			info->dir_y = -1;
		}
		k++;
	}
}

void	init_mapinfo(t_params *p)
{

	init_playerpos(p->map, &p->info);
	p->info.chunk_x = p->vmlx.size_winx / p->info.size_x;
	p->info.chunk_y = p->vmlx.size_winy / p->info.size_y;
}

t_cam	init_cam(void)
{
	t_cam	cam;

	cam.plane_x = 0;
	cam.plane_y = 0.66;
	cam.hit = 0;
	return (cam);
}

int	init_all(t_params *p)
{
	p->info = count_points_in_tab(p->v.map_data);
	p->map = init_map(p->v.map_data, p->info);
	if (!p->map)
		return (1);
	init_mapinfo(p);
	p->cam = init_cam();
	return (0);
}