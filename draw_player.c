/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:56:23 by ahajji            #+#    #+#             */
/*   Updated: 2023/12/10 15:57:11 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void    draw_player(t_cub3d *data)
{
    int i = data->py - 1;
	int j = 0;
	
	while (i < data->py + 1)
	{
		j = data->px - 1;
		while (j < data->px + 1)
		{
			mlx_put_pixel(data->img_map, j, i, 0xFF0000FF);
			j++;
		}
		i++;
	}
}