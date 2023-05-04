/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:11:01 by rgarcia           #+#    #+#             */
/*   Updated: 2023/05/03 17:11:37 by rgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	load_single_text(t_tex *tex, t_varmlx vmlx, char *texture_path)
{
	tex->text = mlx_xpm_file_to_image(vmlx.mlx_ptr, texture_path, \
		&tex->width_img, &tex->height_img);
	if (tex->text == NULL)
		return (1);
	tex->text_adr = mlx_get_data_addr(tex->text, \
		&tex->bits_per_pixel, &tex->line_length, &tex->endian);
	if (tex->text_adr == NULL)
		return (1);
	return (0);
}

t_tex	*text_error(t_tex *tex, t_varmlx vmlx, int mode)
{
	if (mode == 0)
		return (NULL);
	if (mode == 1)
	{
		mlx_destroy_image(vmlx.mlx_ptr, tex[0].text);
		return (NULL);
	}
	if (mode == 2)
	{
		mlx_destroy_image(vmlx.mlx_ptr, tex[0].text);
		mlx_destroy_image(vmlx.mlx_ptr, tex[1].text);
		return (NULL);
	}
	if (mode == 3)
	{
		mlx_destroy_image(vmlx.mlx_ptr, tex[0].text);
		mlx_destroy_image(vmlx.mlx_ptr, tex[1].text);
		mlx_destroy_image(vmlx.mlx_ptr, tex[2].text);
		return (NULL);
	}
	return (NULL);
}

t_tex	*load_all_textures(t_varmlx vmlx, t_vars v)
{
	t_tex	*tex;
	int		i;

	tex = malloc(sizeof(t_tex) * 4);
	if (!tex)
		return (NULL);
	i = 0;
	while (i < 4)
	{
		tex[i].text = NULL;
		tex[i].text_adr = NULL;
		i++;
	}
	if (load_single_text(&tex[0], vmlx, v.east) == 1)
		return (text_error(tex, vmlx, 0));
	if (load_single_text(&tex[1], vmlx, v.south) == 1)
		return (text_error(tex, vmlx, 1));
	if (load_single_text(&tex[2], vmlx, v.west) == 1)
		return (text_error(tex, vmlx, 2));
	if (load_single_text(&tex[3], vmlx, v.north) == 1)
		return (text_error(tex, vmlx, 3));
	return (tex);
}

int	get_text_pixel(t_tex tex)
{
	int	color;

	if (tex.tex_x < 0 || tex.tex_x >= tex.width_img)
		return (0);
	if (tex.tex_y < 0 || tex.tex_y >= tex.height_img)
		return (0);
	color = *(int *)(tex.text_adr + tex.tex_y * tex.line_length \
		+ tex.tex_x * tex.bits_per_pixel / 8);
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
