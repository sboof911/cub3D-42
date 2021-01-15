/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:58:53 by amaach            #+#    #+#             */
/*   Updated: 2021/01/14 11:14:36 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int		ft_sp(char const *s1, char const *set)
{
	int		i;

	i = 0;
	while (ft_strchr(set, s1[i]) && s1[i] != '\0')
		i++;
	return (i);
}

static int		ft_sn(char const *s1, char const *set)
{
	int		i;

	i = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i]))
		i--;
	return (i);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*temp;
	int		i;

	if (!s1)
		return (0);
	if (ft_sp(s1, set) >= ft_sn(s1, set))
	{
		temp = (char *)malloc(1);
		temp[0] = '\0';
		return (temp);
	}
	i = ft_strlen(s1) - (ft_sp(s1, set) + (ft_strlen(s1) - ft_sn(s1, set))) + 1;
	temp = ft_substr(s1, ft_sp(s1, set), i);
	return (temp);
}
