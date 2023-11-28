/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ressources.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:47:32 by nachab            #+#    #+#             */
/*   Updated: 2023/11/28 14:48:29 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    free_split_array(char **arr)
{
    char    **temp;
    int     i;
    
    temp = arr;
    i = 0;
    while (temp[i])
    {
        free(temp[i]);
        i++;
    }
    free(arr);
}