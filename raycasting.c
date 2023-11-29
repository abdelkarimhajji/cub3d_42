/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:37:30 by ahajji            #+#    #+#             */
/*   Updated: 2023/11/29 12:56:25 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_casting(t_cub3d *data, float ray_angle,
	int id_ray, mlx_image_t *img)
{
	double	height_wall;
	int		xstart;
	int		ystart;
	int		xend;
	int		yend;

	data->dist = data->dist * cos(to_rad(ray_angle) - to_rad(data->angle));
	height_wall = ((data->size_shape) * HEIGHT_WIN) / data->dist;
	xstart = id_ray;
	xend = id_ray;
	ystart = (HEIGHT_WIN / 2) - (height_wall / 2);
	yend = (HEIGHT_WIN / 2) + (height_wall / 2);
	if (yend > HEIGHT_WIN)
		yend = HEIGHT_WIN;
	data->texture_offset_x = data->present_texture * img->width;
	data->wall_start = ystart;
	while (ystart < yend)
	{
		data->texture_offset_y = (((float)ystart - (float)data->wall_start)
				/ (float)height_wall) * img->height;
		if (ystart >= 0 && ystart < HEIGHT_WIN)
			mlx_put_pixel(data->img, xstart, (int)ystart,
				get_texel(img, data->texture_offset_x, data->texture_offset_y));
		ystart += 1;
	}
}

void	check_ray_draw_down(t_cub3d *data, float ray_angle, int id_ray)
{
	data->hores_inters_y = floor((data->py / data->size_shape) + 1)
		* data->size_shape;
	data->hores_inters_x = data->px + (data->hores_inters_y - data->py)
		/ tan(to_rad(ray_angle));
	data->next_hor_inters_y = data->hores_inters_y + data->size_shape;
	data->next_hor_inters_x = data->hores_inters_x + ((data->next_hor_inters_y
				- data->hores_inters_y) / tan(to_rad(ray_angle)));
	data->step_hor_y = data->size_shape;
	data->step_hor_x = data->next_hor_inters_x - data->hores_inters_x;
	while (((int)(data->hores_inters_x / data->size_shape)) < data->width_map
		&& ((int)(data->hores_inters_y / data->size_shape)) < data->height_map
		&& data->hores_inters_x >= 0 && data->hores_inters_y >= 0
		&& data->map[(int)(data->hores_inters_y
			/ data->size_shape)][(int)(data->hores_inters_x
			/ data->size_shape)] != '1')
	{
		data->hores_inters_y += data->step_hor_y;
		data->hores_inters_x += data->step_hor_x;
	}
}

void	check_ray_draw_up(t_cub3d *data, float ray_angle, int id_ray)
{
	data->hores_inters_y = floor((data->py / data->size_shape))
		* data->size_shape;
	data->hores_inters_x = data->px - ((data->py - data->hores_inters_y)
			/ tan(to_rad(ray_angle)));
	data->next_hor_inters_y = data->hores_inters_y - data->size_shape;
	data->next_hor_inters_x = data->hores_inters_x - ((data->hores_inters_y
				- data->next_hor_inters_y) / tan(to_rad(ray_angle)));
	data->step_hor_y = data->size_shape;
	data->step_hor_x = data->next_hor_inters_x - data->hores_inters_x;
	while (((int)(data->hores_inters_x / data->size_shape)) < data->width_map
		&& ((int)((data->hores_inters_y - 1)
				/ data->size_shape)) < data->height_map
		&& data->hores_inters_x >= 0 && data->hores_inters_y >= 0
		&& data->map[(int)((data->hores_inters_y - 1)
			/ data->size_shape)][(int)(data->hores_inters_x
			/ data->size_shape)] != '1')
	{
		data->hores_inters_y -= data->step_hor_y;
		data->hores_inters_x += data->step_hor_x;
	}
}

void	check_ray_draw_right(t_cub3d *data, float ray_angle, int id_ray)
{
	data->vertcl_inters_x = floor((data->px / data->size_shape) + 1)
		* data->size_shape;
	data->vertcl_inters_y = data->py - ((data->px - data->vertcl_inters_x)
			* tan(to_rad(ray_angle)));
	data->next_ver_inters_x = data->vertcl_inters_x + data->size_shape;
	data->next_ver_inters_y = data->vertcl_inters_y - ((data->vertcl_inters_x
				- data->next_ver_inters_x) * tan(to_rad(ray_angle)));
	data->step_ver_x = data->size_shape;
	data->step_ver_y = data->next_ver_inters_y - data->vertcl_inters_y;
	while (((int)(data->vertcl_inters_x / data->size_shape)) < data->width_map
		&& ((int)(data->vertcl_inters_y / data->size_shape)) < data->height_map
		&& data->vertcl_inters_x >= 0 && data->vertcl_inters_y >= 0
		&& data->map[(int)(data->vertcl_inters_y
			/ data->size_shape)][(int)(data->vertcl_inters_x
			/ data->size_shape)] != '1')
	{
		data->vertcl_inters_y += data->step_ver_y;
		data->vertcl_inters_x += data->step_ver_x;
	}
}

void	check_ray_draw_left(t_cub3d *data, float ray_angle, int id_ray)
{
	data->vertcl_inters_x = floor((data->px / data->size_shape))
		* data->size_shape;
	data->vertcl_inters_y = data->py - ((data->px - data->vertcl_inters_x)
			* tan(to_rad(ray_angle)));
	data->next_ver_inters_x = data->vertcl_inters_x - data->size_shape;
	data->next_ver_inters_y = data->vertcl_inters_y - ((data->vertcl_inters_x
				- data->next_ver_inters_x) * tan(to_rad(ray_angle)));
	data->step_ver_x = data->size_shape;
	data->step_ver_y = data->next_ver_inters_y - data->vertcl_inters_y;
	while (((int)((data->vertcl_inters_x - 1)
			/ data->size_shape)) < data->width_map
		&& ((int)(data->vertcl_inters_y / data->size_shape)) < data->height_map
		&& data->vertcl_inters_x >= 0 && data->vertcl_inters_y >= 0
		&& data->map[(int)(data->vertcl_inters_y
			/ data->size_shape)][(int)((data->vertcl_inters_x - 1)
			/ data->size_shape)] != '1')
	{
		data->vertcl_inters_y += data->step_ver_y;
		data->vertcl_inters_x -= data->step_ver_x;
	}
}
