/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 16:59:27 by nachab            #+#    #+#             */
/*   Updated: 2023/11/27 12:55:15 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_map_line(char *line)
{
	while (*line)
	{
		if (*line != '0' && *line != '1' && *line != 'N' && *line != 'S'
			&& *line != 'E' && *line != 'W' && *line != ' ' && *line != '\t'
			&& *line != '\n')
			return (1);
		line++;
	}
	return (0);
}

// returns 1 if line isn't empty
int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

void	check_map(t_cub3d *data)
{
	int	i;

	i = 0;
	while (data->map[i] != NULL)
	{
		if (is_map_line(data->map[i]) == 1 || !empty_line(data->map[i]))
		{
			printf("Error, Map can only be composed of 01NSWE.\n");
			exit(1);
		}
		i++;
	}
}

void	check_dimensions(t_cub3d *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] && data->map[i][j] != '\n')
			j++;
		if (j > 30)
		{
			printf("Column width surpassed (max 30)\n");
			exit(1);
		}
		i++;
	}
	if (i > 30)
	{
		printf("Row height surpassed (max 20)");
		exit(1);
	}
}
