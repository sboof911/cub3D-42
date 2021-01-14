/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:27:57 by amaach            #+#    #+#             */
/*   Updated: 2021/01/13 16:55:07 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	j;
	char			*str;

	str = (char *)s;
	j = (unsigned char)c;
	i = 0;
	if (j == '\0')
		return (str + ft_strlen(str));
	while (str[i] != '\0')
	{
		if (str[i] == j)
			return (str + i);
		i++;
	}
	return (NULL);
}
