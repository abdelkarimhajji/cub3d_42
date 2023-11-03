/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:39:17 by ahajji            #+#    #+#             */
/*   Updated: 2023/11/03 12:41:22 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void       move_mouse(double xp, double yp, void *param)
{
    t_cub3d *data = (t_cub3d *)param;
    
    if (xp >= 0 && xp <= width_win && yp >= 0 && yp <= height_win)
    {
        if(xp > data->old_x)
        {
            data->angle += (speed_rotate + 0.1);
            if(data->angle >= 360)
            data->angle -= 360;
        }
        else
        {
            data->angle-= speed_rotate;
            if (data->angle <= 0)
            data->angle += 360;            
        }
        data->old_x = xp;
    }
}
