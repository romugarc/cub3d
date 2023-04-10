#include "cub3d.h"

void	draw_line(t_cam cam, t_data img, t_tex tex, int x, int s_wy)
{
	int		y;
	int		big;
	double	step;
	double	tex_start;
	float	slice_height;
	unsigned int	color;
	int	green;
	int	blue;
	int	red;

	//printf("a%d\t", tex.tex_x);
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
	//color = 0x0000FFFF;
	red = 0x00FF0000;
	blue = 0x00FFFF00;
	green = 0x0000FF00;
	//slice_height = (float)(s_wy / cam.perpwalldist);
	step = 1.0 * tex.height_img / cam.lineheight;
	//printf("%d\t%d\n", tex.height_img, tex.width_img);
	//step = 1.0 * tex.height_img / slice_height;
	tex_start = (y - s_wy / 2 + cam.lineheight / 2) * step;
	//printf("%f\t%f\n", step, tex_start);
	//tex.tex_y = 0;
	while (y < big)
	{
		/*if (cam.side == 0)
			my_mlx_pixel_put(&img, x, y, color/2);
		else if (cam.side == 1)
			my_mlx_pixel_put(&img, x, y, red);
		else if (cam.side == 2)
			my_mlx_pixel_put(&img, x, y, color/2);
		else if (cam.side == 3)
			my_mlx_pixel_put(&img, x, y, blue);*/
		////
		if (cam.side == 0)
		{
			tex.tex_y = (int)tex_start & (tex.height_img - 1);
			//printf("x%d\ty%d\t", tex.tex_x, tex.tex_y);
			color = get_text_pixel(tex);
			//printf("%d\t", color);
			my_mlx_pixel_put(&img, x, y, color);
			tex_start += step;
		}
		else if (cam.side == 1)
		{
			tex.tex_y = (int)tex_start & (tex.height_img - 1);
			//printf("x%d\ty%d\t", tex.tex_x, tex.tex_y);
			color = get_text_pixel(tex);
			//printf("%d\t", color);
			my_mlx_pixel_put(&img, x, y, color);
			tex_start += step;
		}
		else if (cam.side == 2)
		{
			tex.tex_y = (int)tex_start & (tex.height_img - 1);
			//printf("x%d\ty%d\t", tex.tex_x, tex.tex_y);
			color = get_text_pixel(tex);
			//printf("%d\t", color);
			my_mlx_pixel_put(&img, x, y, color);
			tex_start += step;
		}
		else if (cam.side == 3)
		{
			tex.tex_y = (int)tex_start & (tex.height_img - 1);
			//printf("x%d\ty%d\t", tex.tex_x, tex.tex_y);
			color = get_text_pixel(tex);
			//printf("%d\t", color);
			my_mlx_pixel_put(&img, x, y, color);
			tex_start += step;
		}
		y++;
	}
}

void	drawing_map(t_params *p)
{
	p->img.img = mlx_new_image(p->vmlx.mlx_ptr, p->vmlx.size_winx, p->vmlx.size_winy);
	p->img.addr = mlx_get_data_addr(p->img.img, &p->img.bits_per_pixel, &p->img.line_length, &p->img.endian);
	floor_cast(p);
	load_textures(p, p->v.east, 0);
	load_textures(p, p->v.south, 1);
	load_textures(p, p->v.west, 2);
	load_textures(p, p->v.north, 3);
	raycast_lines(p);
	mlx_put_image_to_window(p->vmlx.mlx_ptr, p->vmlx.win_ptr, p->img.img, 0, 0);
	mlx_destroy_image(p->vmlx.mlx_ptr, p->img.img);
	free(p->tex[0].text);
	free(p->tex[0].text_adr);
	free(p->tex[1].text);
	free(p->tex[1].text_adr);
	free(p->tex[2].text);
	free(p->tex[2].text_adr);
	free(p->tex[3].text);
	free(p->tex[3].text_adr);
}