/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:44:49 by amaach            #+#    #+#             */
/*   Updated: 2019/10/24 19:21:54 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*help;
	int		i;
	size_t	j;

	help = (char *)haystack;
	i = 0;
	j = 0;
	if (needle[i] == 0)
		return (help);
	while (haystack[j] != '\0' && len > j)
	{
		i = 0;
		while (haystack[j + i] == needle[i] && needle[i] != '\0' && i + j < len)
		{
			i++;
			if (needle[i] == '\0')
				return (help + j);
		}
		j++;
	}
	return (NULL);
}
