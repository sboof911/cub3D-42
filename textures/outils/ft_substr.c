/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 17:53:53 by amaach            #+#    #+#             */
/*   Updated: 2021/01/13 16:55:22 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*temp;
	size_t			j;
	unsigned int	start1;

	start1 = start;
	if (!s)
		return (0);
	j = 0;
	if (start > ft_strlen(s))
		len = 0;
	if (!(temp = (char *)malloc(sizeof(char) * len + 1)))
		return (0);
	while (start < start1 + (unsigned int)len && s[start])
	{
		temp[j] = s[start];
		start++;
		j++;
	}
	temp[j] = '\0';
	return (temp);
}
