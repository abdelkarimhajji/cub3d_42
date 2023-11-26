/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 16:48:29 by nachab            #+#    #+#             */
/*   Updated: 2022/10/11 12:55:09 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pt;

	pt = malloc(count * size);
	if (pt == 0)
		return (pt);
	ft_bzero(pt, count * size);
	return (pt);
}
/*
int	main(void)
{
	char	*s = ft_calloc(10, 10);
	char	*pt = calloc(10, 10);
	s[9] = 'w';
	pt[9] = 'w';
	printf("%c\n", s[9]);
	printf("%c\n", pt[9]);
	return (0);
}
*/
