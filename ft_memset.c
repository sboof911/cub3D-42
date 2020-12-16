/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:52:44 by amaach            #+#    #+#             */
/*   Updated: 2019/10/14 13:20:10 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	int					i;
	unsigned char		*b;

	i = 0;
	b = s;
	while (i < (int)n)
	{
		b[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
