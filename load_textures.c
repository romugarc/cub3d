#include "cub3d.h"

int	load_textures(t_params *p, char *texture_path, int i)
{
	p->tex[i].text = mlx_xpm_file_to_image(p->vmlx.mlx_ptr, texture_path, &p->tex[i].width_img, &p->tex[i].height_img);
	if (p->tex[i].text == NULL)
		return (1);
	p->tex[i].text_adr = mlx_get_data_addr(p->tex[i].text, &p->tex[i].bits_per_pixel, &p->tex[i].line_length, &p->tex[i].endian);
	if (p->tex[i].text_adr == NULL)
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