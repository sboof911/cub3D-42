/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 20:35:28 by amaach            #+#    #+#             */
/*   Updated: 2019/10/22 15:56:35 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	o;

	j = ft_strlen(src);
	i = 0;
	k = ft_strlen(dst);
	o = k;
	if (k >= size)
		return (j + size);
	while (size - 1 != o && src[i] != '\0')
	{
		dst[o] = src[i];
		i++;
		o++;
	}
	if (o < size)
		dst[o] = '\0';
	return (j + k);
}
