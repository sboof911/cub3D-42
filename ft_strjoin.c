/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:24:19 by amaach            #+#    #+#             */
/*   Updated: 2019/10/24 18:06:57 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	t;
	char	*temp;

	if (!s1)
		return (0);
	if (!s2)
		return (ft_strdup(s1));
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	t = -1;
	if (!(temp = (char *)malloc(sizeof(char) * (i + j + 1))))
		return (0);
	if (!temp)
		return (NULL);
	while (++t < i + j)
	{
		if (t < i)
			temp[t] = s1[t];
		else
			temp[t] = s2[t - i];
	}
	temp[t] = '\0';
	return (temp);
}
