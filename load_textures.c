#include "cub3d.h"

int	load_textures(t_tex *tex, t_varmlx vmlx, char *texture_path)
{
	tex->text = mlx_xpm_file_to_image(vmlx.mlx_ptr, texture_path, &tex->width_img, &tex->height_img);
	if (tex->text == NULL)
		return (1);
	tex->text_adr = mlx_get_data_addr(tex->text, &tex->bits_per_pixel, &tex->line_length, &tex->endian);
	if (tex->text_adr == NULL)
		return (1);
	return (0);
}

int	get_text_pixel(t_tex tex)
{
	int	color;

	if (tex.tex_x < 0 || tex.tex_x >= tex.width_img)
		return (0);
	if (tex.tex_y < 0 || tex.tex_y >= tex.height_img)
		return (0);
	color = *(int *)(tex.text_adr + tex.tex_y * tex.line_length + tex.tex_x * tex.bits_per_pixel / 8);
	return (color);
}

int	get_tex_x(t_cam cam, t_mapinfo info, t_tex tex)
{
	double	wall_x;
	int		tex_x;

	if (cam.side == 0 || cam.side == 2)
		wall_x = info.start_y + cam.perpwalldist * cam.raydir_y;
	else
		wall_x = info.start_x + cam.perpwalldist * cam.raydir_x;
	wall_x -= (int)(wall_x);
	tex_x = (int)(wall_x * (double)tex.width_img);
	if ((cam.side == 0 || cam.side == 2) && cam.raydir_x > 0)
		tex_x = tex.width_img - tex_x - 1;
	if ((cam.side == 1 || cam.side == 3) && cam.raydir_y < 0)
		tex_x = tex.width_img - tex_x - 1;
	return (tex_x);
}