#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include "mlx_linux/mlx.h"
# include "libft/libft.h"
# include "libft/get_next_line.h"

# define 	FLOOR = 0;
# define	WALL = 1;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_varmlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	*title;
	int		size_winx;
	int		size_winy;
}	t_varmlx;

typedef struct s_vars
{
	char	**map_data;
	char	*gnl_ret;
	int		fd;
}	t_vars;

typedef	struct s_mapinfo
{
	int	chunk_x;
	int	chunk_y;
	int	points;
	int	size_x;
	int	size_y;
}	t_mapinfo;

typedef struct s_map
{
	int	x;
	int	y;
	char	type;
}	t_map;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	parse_file(t_vars *vars);
#endif