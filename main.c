#include "cub3d.h"

void	error_handler(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error\nOnly one argument allowed\n", 2);
		exit(EXIT_FAILURE);
	}
	if (iscubfile(argv[1]) == 0)
	{
		ft_putstr_fd("Error\nNot .cub file\n", 2);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	t_params	p;

	error_handler(argc, argv);
	init_vars(&p.vmlx, &p.v, argv[1]);
	parse_file(&p.v);
	if (init_all(&p) == 1)
		return (1);
	p.vmlx.mlx_ptr = mlx_init(); //sécuriser malloc?
	p.vmlx.win_ptr = mlx_new_window(p.vmlx.mlx_ptr, \
		p.vmlx.size_winx, p.vmlx.size_winy, p.vmlx.title);
	drawing_map(&p);
	mlx_hook(p.vmlx.win_ptr, 2, 1L << 0, key_hook, &p);
	mlx_hook(p.vmlx.win_ptr, 17, 1L << 0, close_window, &p);
	mlx_loop(p.vmlx.mlx_ptr);
	return (0);
}
