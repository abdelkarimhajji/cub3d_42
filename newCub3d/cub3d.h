/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:19:16 by ahajji            #+#    #+#             */
/*   Updated: 2023/10/25 10:47:15 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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


#define width_win  2000
#define height_win  900
#define size_shape 26
#define speed_rotate 0.5
#define move_step 1
typedef struct s_cub3d
{
    mlx_t       *mlx;
    mlx_image_t *img;
    int         width_map;
    int         height_map;
    float       px;
    float       py;
    float       angle;
    
}               t_cub3d;
