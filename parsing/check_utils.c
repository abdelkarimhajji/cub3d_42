/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 13:02:55 by nachab            #+#    #+#             */
/*   Updated: 2023/12/11 14:21:13 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_comma(char *line)
{
	int	count;

	count = 0;
	while (*line)
	{
		if (*line == ',')
		{
			if (*(line + 1) == ',')
			{
				printf("Please enter a valid rgb value\n");
				exit(1);
			}
			count++;
		}
		line++;
	}
	if (count > 3)
	{
		printf("Please enter a valid rgb value\n");
		exit(1);
	}
}

int	beflastline(char **map, int y)
{
	if (map[y + 1] != NULL && map[y + 2] != NULL)
		return (1);
	return (0);
}
