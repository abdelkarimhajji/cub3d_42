/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouve_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:39:17 by ahajji            #+#    #+#             */
/*   Updated: 2023/11/09 14:07:51 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_mouse(double xp, double yp, void *param)
{
	t_cub3d	*data;

	data = (t_cub3d *)param;
	if (xp >= 0 && xp <= WIDTH_WIN && yp >= 0 && yp <= HEIGHT_WIN)
	{
		if (xp > data->old_x)
		{
			data->angle += (SPEED_ROTATE + 0.1);
			if (data->angle >= 360)
				data->angle -= 360;
		}
		else
		{
			data->angle -= SPEED_ROTATE;
			if (data->angle <= 0)
				data->angle += 360;
		}
		data->old_x = xp;
	}
}
