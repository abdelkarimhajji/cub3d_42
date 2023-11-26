/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:56:01 by nachab            #+#    #+#             */
/*   Updated: 2022/09/30 16:02:36 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = s;
	if (n > 0)
	{
		while (i < n)
		{
			str[i] = 0;
			i++;
		}
	}
}
/*
int	main(void)
{
	char	*s = "hello";
	printf("%d\n", ft_bzero(s, 2));
	printf("%d", bzero(s, 2));
	return (0);
}
*/