/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:45:11 by nachab            #+#    #+#             */
/*   Updated: 2022/10/13 23:43:24 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	d;
	size_t	s;
	size_t	j;

	if (!dst && dstsize == 0)
		return (0);
	j = ft_strlen(dst);
	s = ft_strlen(src);
	if (dstsize <= j)
		return (dstsize + s);
	i = 0;
	d = j;
	while (src[i] && j + 1 < dstsize)
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (d + s);
}
