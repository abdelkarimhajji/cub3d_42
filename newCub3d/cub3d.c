/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:18:46 by ahajji            #+#    #+#             */
/*   Updated: 2023/10/24 11:47:25 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw()
{
    
}

int main(int ac, char **av)
{
    t_cub3d     data;
    
    data.mlx = mlx_init(width_win, height_win, "cub3d", true);
    if(!data.mlx)
        return (1);
    data.img = mlx_new_image(data.mlx, width_win, height_win);
    if(!(data.img || mlx_image_to_window(data.mlx, data.img, 0, 0)))
        return(1);
    mlx_loop_hook(data.mlx, draw, &data);
    mlx_loop(data.mlx);
    mlx_terminate(data.mlx);
    return (0);
}