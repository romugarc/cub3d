/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgarcia <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:09:08 by rgarcia           #+#    #+#             */
/*   Updated: 2023/05/03 17:09:09 by rgarcia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	movement(int keycode, t_params *prms)
{
	if (keycode == 119)
	{
		prms->info.start_x += prms->info.dir_x;
		prms->info.start_y += prms->info.dir_y;
	}
	else if (keycode == 115)
	{
		prms->info.start_x -= prms->info.dir_x;
		prms->info.start_y -= prms->info.dir_y;
	}
	else if (keycode == 100)
	{
		prms->info.start_x += prms->cam.plane_x;
		prms->info.start_y += prms->cam.plane_y;
	}
	else if (keycode == 97)
	{
		prms->info.start_x -= prms->cam.plane_x;
		prms->info.start_y -= prms->cam.plane_y;
	}
}
