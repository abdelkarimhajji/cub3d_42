/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:00:15 by nachab            #+#    #+#             */
/*   Updated: 2023/12/11 13:04:35 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*r_rgb_str(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != 'F' && line[i] != 'C' && line[i] != ' '
			&& line[i] != '\t')
			return (&line[i]);
		i++;
	}
	return (NULL);
}

void	check_rgb_str(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		if (str[i][0] == '\n')
		{
			printf("Please fix the rgb values\n");
			exit (1);
		}
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]) && str[i][j] != '\n')
			{
				printf("Please fix the rgb values\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
}

int	nb_rgb_elem(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

long	return_hex_rgb(char *line)
{
	char	**values;
	long	hex_val;
	int		r;
	int		g;
	int		b;

	values = ft_split(line, ',');
	if (nb_rgb_elem(values) > 3)
		exit(1);
	check_rgb_str(values);
	if (values && values[0] && values[1] && values[2])
	{
		r = ft_atoi(values[0]);
		g = ft_atoi(values[1]);
		b = ft_atoi(values[2]);
		free_2dchar_array(values);
		if ((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0
				&& b <= 255))
		{
			hex_val = ((long)r << 24) | ((long)g << 16) | (long)b << 8 | (1
					* 255);
			return (hex_val);
		}
	}
	return (-1);
}

long	rgb_to_hex(char *line)
{
	check_comma(line);
	return (return_hex_rgb(line));
}
