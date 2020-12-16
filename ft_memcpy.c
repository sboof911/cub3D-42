/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:40:17 by amaach            #+#    #+#             */
/*   Updated: 2019/10/23 22:58:46 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;

	i = -1;
	s = (unsigned char *)src;
	d = dst;
	if (!(dst || src))
		return (0);
	while (++i < n)
		d[i] = s[i];
	return (dst);
}
