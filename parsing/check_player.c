/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahajji <ahajji@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:59:29 by nachab            #+#    #+#             */
/*   Updated: 2023/11/30 15:16:22 by ahajji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	duplicate_player(t_cub3d *data)
{
	int	i;
	int	j;
	int	v;

	i = 0;
	v = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
				v++;
			j++;
		}
		i++;
	}
	if (v != 1)
	{
		printf("Please provide a player position in the map (NO DUPLICATES)\n");
		exit(1);
	}
}

void	get_player_pos(t_cub3d *data)
{
	int	i;
	int	j;
	int	v;

	i = 0;
	v = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				data->player.direction = data->map[i][j];
				data->player.i = i;
				data->player.j = j;
				v++;
				return ;
			}
			j++;
		}
		i++;
	}
}
