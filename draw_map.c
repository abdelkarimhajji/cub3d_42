/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:21:24 by ahajji            #+#    #+#             */
/*   Updated: 2023/11/03 12:36:07 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_rectangle(int x, int y, t_cub3d *data, uint32_t color)
{
    int i;
    int j;
	
    i = x;
    j = y;
    while (y <  data->size_shape + j)
    {
        x = i;
        while (x <  data->size_shape + i)
        {
            mlx_put_pixel(data->img_map, x, y, color);
            x++;
        }
        y++;
    }
}

void draw_map(t_cub3d *data, int mode)
{
	int i = 0;
    int j = 0;
	
	while (j < data->height_map)
    {
        i = 0;
        while (i < data->width_map)
        {
            if (myMap[j][i] == '1')
                draw_rectangle( i * data->size_shape, j * data->size_shape, data, 0xFFFFFFFF);
			if (myMap[j][i] == '0' || (mode == 0 && myMap[j][i] == 'P'))
				draw_rectangle( i * data->size_shape, j * data->size_shape, data, 0x000000FF);
            if(myMap[j][i] == ' ')
                draw_rectangle( i * data->size_shape, j * data->size_shape, data, 0xFF000033);
            if(myMap[j][i] == 'P' && mode)
            {
				draw_rectangle(i * data->size_shape, j * data->size_shape, data, 0x000000FF);
				mlx_put_pixel(data->img, data->px = (i * data->size_shape) + 13,
                data->py = (j * data->size_shape) + 13, 0xFF0000FF);
            }
            i++;
        }
        j++;
    }
} 

void    draw_view_angle(t_cub3d *data)
{
    int i = 0;
    float ray_angle = data->angle - (view_angle / 2);
    if (ray_angle < 0)
        ray_angle = 360 + ray_angle;
    int id_ray = 0;
    while (i < data->number_rays)
    {
        if (ray_angle >= 360)
            ray_angle -= 360;
        check_ray_draw(data, ray_angle, id_ray);
        id_ray++;
        ray_angle += (view_angle / data->number_rays) ;
        i++;
    }
}
