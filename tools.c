/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:52:59 by ahajji            #+#    #+#             */
/*   Updated: 2023/11/03 11:54:34 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float   to_rad(float degree)
{
    return(degree * (M_PI / 180));
}
void    draw_line_dda(t_cub3d *data, float  x2, float  y2, uint32_t color)
{
    float   dx;
    float   dy;
    float   x1;
    float   y1;
    int i;
    
    i = 0;
    x1 = data->px;
    y1 = data->py;
    dx = x2 - x1;
    dy = y2 - y1;
    if (fabs(dx) > fabs(dy))
        data->steps = fabs(dx);
    else
        data->steps = fabs(dy);
    data->increamentx = dx / data->steps;
    data->increamenty = dy / data->steps;
    while (i <= data->steps)
    {
        mlx_put_pixel(data->img_map, round(x1), round(y1), color);
        x1 += data->increamentx;
        y1 += data->increamenty;        
        i++;
    }
}

float   distance_between_points(float x1, float y1, float x2, float y2)
{
    return  (sqrt(pow((x2 - x1), 2) +  pow((y1 - y2), 2)));
}
