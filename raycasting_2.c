/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:32:35 by ahajji            #+#    #+#             */
/*   Updated: 2023/11/25 13:35:14 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	call_raycasting(t_cub3d *data, float ray_angle, int id_ray)
{
	if (data->distance_horz < data->distance_vert)
	{
		data->dist = data->distance_horz;
		if (ray_angle >= 180 && ray_angle <= 360)
			ray_casting(data, ray_angle, id_ray, data->textures.no_texture);
		else
			ray_casting(data, ray_angle, id_ray, data->textures.so_texture);
		data->presentTexture = (data->hores_inters_x / data->size_shape) - ((int)(data->hores_inters_x / data->size_shape));
		draw_line_dda(data, data->hores_inters_x, data->hores_inters_y,
			0xFF0000FF);
	}
	else
	{
		data->dist = data->distance_vert;
		if (ray_angle >= 90 && ray_angle <= 270)
			ray_casting(data, ray_angle, id_ray, data->textures.ea_texture);
		else
			ray_casting(data, ray_angle, id_ray, data->textures.we_texture);
		data->presentTexture = (data->vertcl_inters_y / data->size_shape) - ((int)(data->vertcl_inters_y / data->size_shape));
		draw_line_dda(data, data->vertcl_inters_x, data->vertcl_inters_y,
			0xFF0000FF);
	}
}
