/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 20:02:19 by nachab            #+#    #+#             */
/*   Updated: 2022/10/16 23:33:17 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	len(int n)
{
	long	nb;
	long	size;

	size = 0;
	nb = n;
	if (n <= 0)
	{
		nb *= -1;
		size++;
	}
	while (nb > 0)
	{
		size++;
		nb /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*pt;
	long	i;
	long	nb;

	i = len(n) + 1;
	nb = n;
	pt = (char *)malloc(i-- * sizeof(char));
	if (pt == 0)
		return (0);
	if (nb == 0)
		pt[0] = '0';
	pt[i--] = '\0';
	if (nb < 0)
	{
		nb *= -1;
		pt[0] = '-';
	}
	while (nb > 0)
	{
		pt[i--] = nb % 10 + 48;
		nb /= 10;
	}
	return (pt);
}
/*
int	main(void)
{
	char	*pt = ft_itoa(-500);
	printf("%s\n", pt);
	printf("%s\n", ft_itoa(0));
	return (0);
}*/
