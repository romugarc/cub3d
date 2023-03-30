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
# define	TRUE 2
# define	FALSE 3

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
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*floor;
	char	*ceiling;
	char	*gnl_ret;
	char	**map_data;
	char	*map_in_str;
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
//parsing
int		map_char(char c);
int		check_path_and_colors(t_vars *vars);
int		strlen_itoc(char *str, int i, char c);
int		strlen_itoc(char *str, int i, char c);
void	fail(char *str);
void	check_map(t_vars *vars);
void	parse_file(t_vars *vars);
void	get_east(t_vars *vars, int i);
void	get_west(t_vars *vars, int i);
void	get_floor(t_vars *vars, int i);
void	get_south(t_vars *vars, int i);
void	get_north(t_vars *vars, int i);
void	get_ceiling(t_vars *vars, int i);
void	check_all_color(t_vars *vars, int i);
char	**ft_splitv2(const char *str, char c);

#endif