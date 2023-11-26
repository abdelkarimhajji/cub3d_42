/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:59:24 by nachab            #+#    #+#             */
/*   Updated: 2023/11/25 16:59:25 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    check_walls(t_cub3d *data)
{
    int i;
    int j;
    
    i = 0;
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j] && data->map[i][j] != '\n')
        {
            if (i == 0 || data->map[i + 1] == NULL)
            {
                if (data->map[i][j] != '1')
                    exit (1);
            }
            else if (j == 0 || data->map[i][j + 1] == '\n')
            {
                if (data->map[i][j] != '1')
                    exit (1);
            }
            j++;
        }
        i++;
    }
}

size_t get_index(char *line, char *needle)
{
    size_t i;

    i = 0;
    while (*line && line != needle)
    {
        line++;
        i++;
    }
    return (i);
}

int check_cells(t_cub3d *data, int i, int j)
{
    if ((data->map[i][j + 1] != '0' && data->map[i][j + 1] != data->player.direction && data->map[i][j + 1] != '1'))
    {
        return (1);
    }
    else if ((data->map[i][j - 1] != '0' && data->map[i][j - 1] != data->player.direction && data->map[i][j - 1] != '1'))
    {
        return (1);
    }
    else if ((data->map[i + 1][j] != '0' && data->map[i + 1][j] != data->player.direction && data->map[i + 1][j] != '1') || get_index(data->map[i], &data->map[i][j]) > ft_strlen(data->map[i + 1]))
    {
        return (1);
    }
    else if ((data->map[i - 1][j] != '0' && data->map[i - 1][j] != data->player.direction && data->map[i - 1][j] != '1') || get_index(data->map[i], &data->map[i][j]) > ft_strlen(data->map[i - 1]))
    {
        return (1);
    }
    return (0);
}

void    check_valid_path(t_cub3d *data)
{
    int i;
    int j;

    i = 0;
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j] && data->map[i][j] != '\n')
        {
            if ((i > 0 && j > 0) && (data->map[i][j] == data->player.direction || data->map[i][j] == '0') && (data->map[i + 1] != NULL))
            {
                if (check_cells(data, i, j) == 1)
                {
                    printf("Map path isn't valid\n");
                    exit (1);
                }
            }
            j++;
        }
        i++;
    }
}