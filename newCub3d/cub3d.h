/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:19:16 by ahajji            #+#    #+#             */
/*   Updated: 2023/11/02 21:06:00 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <limits.h>
#include "./MLX/MLX42.h"

char myMap[12][30] = {
    "111111111111111111111111111111",
    "100000001010101000110000000001",
    "100000010001001000100000000001",
    "111110000100110101100000000001",
    "1000001P0001010000000000000001",
    "100000000111110000000000000001",
    "100000100000000001111000000001",
    "100000010000000000000000000001",
    "100000001111110000011110000001",
    "100000000000001110000000000001",
    "100000000000000000000000000001",
    "111111111111111111111111111111"
};


#define width_win  2000
#define height_win  900
#define speed_rotate 0.5
#define move_step 0.2
#define move_step_v 0.6
#define view_angle 60

typedef struct s_cub3d
{
    mlx_t       *mlx;
    mlx_image_t *img;
    mlx_image_t *img_map;
    int         width_map;
    int         height_map;
    int         size_map;
    int         size_shape;
    float       px;
    float       py;
    float       angle;
    float       number_rays;
    mlx_texture_t *load_img;
    double      old_x;
}               t_cub3d;
