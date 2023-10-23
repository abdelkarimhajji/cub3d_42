/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:01:47 by ahajji            #+#    #+#             */
/*   Updated: 2023/10/22 18:11:31 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./MLX/MLX42.h"

char myMap[11][16] = {
    "111111111111111",
    "100000000010101",
    "100000000001001",
    "11111000010011",
    "1000000P1001011",
    "100000000111111",
    "100000100000001",
    "100000000000001",
    "111111001111111",
    "100000000000001",
    "111111111111111"
};

typedef struct  s_data
{
    mlx_t       *mlx;
    mlx_image_t *img;
	void	    *mlx_win;
    void        *mlx_img;
    int         lengx;
    int         lengy;
    int         width;
    int         n_rays;
    double         xray;
    double         yray;
    double          dist;
    double        ray_angle;
    double         xp;
    double         yp;  
    int         start_x_p;
    int         start_y_p;
    double      second_point_x;
    double      second_point_y;
    double      second_point_ver_x;
    double      second_point_ver_y;
    int         corner;
    
}               t_data;
