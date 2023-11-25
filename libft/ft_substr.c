/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 17:56:25 by nachab            #+#    #+#             */
/*   Updated: 2022/10/16 17:26:02 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*pt;

	i = 0;
	pt = (char *)malloc((len + 1) * sizeof(char));
	if (pt == 0 || !s)
		return (0);
	if (start < ft_strlen(s))
	{
		while (i < len && s[i])
			pt[i++] = s[start++];
	}
	pt[i] = '\0';
	return (pt);
}
