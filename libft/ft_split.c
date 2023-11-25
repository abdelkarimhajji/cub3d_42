/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nachab <nachab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:04:26 by nachab            #+#    #+#             */
/*   Updated: 2022/10/09 14:54:33 by nachab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numb_elem(char const *s, unsigned char c)
{
	size_t	i;
	int		valid;
	int		count;

	i = 0;
	valid = 1;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && valid)
		{
			valid = 0;
			count++;
		}
		else if (s[i] == c && valid == 0)
			valid = 1;
		i++;
	}
	return (count);
}

static char	*copy(char const *src, unsigned char c, int *index)
{
	int		i;
	int		len;
	char	*pt;

	i = 0;
	len = 0;
	while (src[len] && src[len] != c)
		len++;
	pt = (char *)malloc(len + 1 * sizeof(char));
	while (src[i] && i < len)
	{
		pt[i] = src[i];
		i++;
	}
	*index = len;
	pt[i] = '\0';
	return (pt);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		len;
	char	**arr;

	i = 0;
	j = 0;
	len = 0;
	if (!s)
		return (0);
	arr = malloc((numb_elem(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (0);
	while (s[i])
	{
		if (s[i] != (unsigned char)c)
		{
			arr[j++] = copy(&s[i], c, &len);
			i += len - 1;
		}
		i++;
	}
	arr[j] = 0;
	return (arr);
}
/*
int	main(void)
{
	char	*word = "it's fucking working";
	char	**arr = ft_split(word, ' ');
	printf("%s\n", arr[2]);
	return (0);
}*/
