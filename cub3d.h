#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <math.h>
# include "mlx_linux/mlx.h"
# include "libft/libft.h"
# include "libft/get_next_line.h"

# define 	FLOOR = 0
# define	WALL = 1
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
	int		color_floor;
	int		color_ceiling;
	int		fd;
}	t_vars;

typedef	struct s_mapinfo
{
	int	chunk_x;
	int	chunk_y;
	int	points;
	int	size_x;
	int	size_y;
	double	start_x;
	double	start_y;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
}	t_mapinfo;

typedef struct	s_cam
{
	double	camera_x;
	double	plane_x;
	double	plane_y;
	double	raydir_x;
	double	raydir_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perpwalldist;
	int		hit;
	int		side;
	int		lineheight;
	int		step_x;
	int		step_y;
	int		draw_start;
	int		draw_end;
	double	rad;
	double	movespeed;
}	t_cam;

typedef struct s_tex
{
	void	*text;
	char	*text_adr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width_img;
	int		height_img;
}	t_tex;

typedef struct s_map
{
	int	x;
	int	y;
	char	type;
}	t_map;

typedef struct	s_params
{
	t_map		*map;
	t_cam		cam;
	t_mapinfo	info;
	t_vars		v;
	t_varmlx	vmlx;
	t_data		img;
	t_tex		tex;
}	t_params;


void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	parse_file(t_vars *vars);
void	ft_free_tab(char **tab);
void	init_vars(t_varmlx *varmlx, t_vars *vars, char *file);
int		init_all(t_params *p);
t_map	*init_map(char **parsed_data, t_mapinfo info);
int		init_playerpos(t_map *cmap, t_mapinfo *info, t_cam *cam);
t_mapinfo	count_points_in_tab(char **tab);
void	movement(int keycode, t_params *prms);
void	rotation_camera(int keycode, t_params *p);
void	floor_cast(t_params	*p);
void	raycast_lines(t_params *p);
int		iscubfile(char *file);
void	drawing_map(t_params *p);
void	draw_line(t_cam cam, t_data img, int x);
int		key_hook(int keycode, t_params *prms);
int		close_window(t_params *prms);
//parsing
void	check_map(t_vars *vars);
void	parse_file(t_vars *vars);
void	get_colors(t_vars *vars);
void	check_vars(t_vars *vars);
void	fail(char *str, t_vars *vars);
void	get_east(t_vars *vars, int i);
void	get_west(t_vars *vars, int i);
void	get_floor(t_vars *vars, int i);
void	get_south(t_vars *vars, int i);
void	get_north(t_vars *vars, int i);
void	get_ceiling(t_vars *vars, int i);
void	check_all_color(t_vars *vars, int i);
char	**ft_splitv2(const char *str, char c);
int		map_char(char c);
int		check_path_and_colors(t_vars *vars);
int		strlen_itoc(char *str, int i, char c);
int		strlen_itoc(char *str, int i, char c);

#endif