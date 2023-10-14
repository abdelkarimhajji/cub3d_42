/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 11:01:19 by ahajji            #+#    #+#             */
/*   Updated: 2023/10/14 19:51:45 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_line(void *mlx_ptr, void *win_ptr, int x1, int y1, int x2, int y2, int color)
{
    int dx = abs(x2 - x1);
    int dy = -abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1)
    {
        mlx_pixel_put(mlx_ptr, win_ptr, x1, y1, color);

        if (x1 == x2 && y1 == y2)
            break;

        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

void    draw_rectangle(int x, int y, void   *mlx, void  *mlx_win)
{
    int tes;
    tes = x;
    int tes2;
    tes2 = y;
    while (y <  30 + tes2)
    {
        x = tes;
        while (x <  30 + tes)
        {
            mlx_pixel_put(mlx, mlx_win, x, y, 0xFFFFFF);
            x++;
        }
        y++;
    }
}

void    draw_player(int x, int y, void   *mlx, void  *mlx_win)
{
    int tes;
    tes = x;
    int tes2;
    tes2 = y;
    while (y <  30 + tes2)
    {
        x = tes;
        while (x <  30 + tes)
        {
            mlx_pixel_put(mlx, mlx_win, x, y, 0x00FF0000);
            x++;
        }
        y++;
    }
}
int my_key_press(int keycode, void *param)
{
    int x = 0;
    int y = 0;
    int i = 0;
    int j = 0;
    t_data *data = (t_data *)param;
    printf("%d\n", keycode);
   
   
    mlx_clear_window(data->mlx, data->mlx_win);
    while (i < 11)
    {
        j = 0;
        x = 0;
        while (j < 16)
        {
            if (myMap[i][j] == '1')
                draw_rectangle( x, y, data->mlx , data->mlx_win);
            if(myMap[i][j] == 'P')
            {
                if (keycode == 124)
                {
                    data->x += 5;
                    draw_player(data->x, data->y , data->mlx , data->mlx_win);
                    data->xp = data->x + 15;
                    data->yp = y + 15;
                }
                if (keycode == 123)
                {
                    data->x -= 5;
                    draw_player(data->x, data->y , data->mlx , data->mlx_win);
                    data->xp = data->x + 15;
                    data->yp = y + 15;
                }
            }
            x += 30;
            j++;
        }
        y += 30;
        i++;
    }
   
draw_line(data->mlx, data->mlx_win, data->xp, data->yp, 300, 300, 0xFFFFFF);
    // You can use the 'data' parameter as needed
    return (0);
}

int	main(void)
{
	t_data data;
    int i = 0;
    int j = 0;
    

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
    i = 0;
    int x = 0;
    int y = 0;
    int xp;
    int yp;
    while (i < 11)
    {
        j = 0;
        x = 0;
        while (j < 16)
        {
            if (myMap[i][j] == '1')
                draw_rectangle( x, y, data.mlx , data.mlx_win);
            if(myMap[i][j] == 'P')
            {
                draw_player(x, y, data.mlx , data.mlx_win);
                data.x = x;
                data.y = y;
                data.xp = x + 15;
                data.yp = y + 15;
            }
            x += 30;
            j++;
        }
        y += 30;
        i++;
    }
    draw_line(data.mlx, data.mlx_win, data.xp, data.yp, 300, 300, 0xFFFFFF);
    // mlx_key_hook(data.mlx_win, my_key_press, &data);
    // mlx_hook(data.mlx_win, 2, 1L<<0, my_key_press, &data);
	mlx_loop(data.mlx);
}
