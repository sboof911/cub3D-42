/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 13:55:17 by amaach            #+#    #+#             */
/*   Updated: 2021/01/13 16:55:25 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#define BUFFER_SIZE 100

int		get_line(int fd, char **str)
{
	int		len;
	char	*buffer;
	char	*temp;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!*str)
		*str = ft_strdup("");
	while (ft_strchr(*str, '\n') == NULL)
	{
		if ((len = read(fd, buffer, BUFFER_SIZE)) < 0)
		{
			free(buffer);
			return (-1);
		}
		buffer[len] = '\0';
		temp = *str;
		*str = ft_strjoin(*str, buffer);
		free(temp);
		if (len == 0 || str[0] == 0)
			break ;
	}
	free(buffer);
	return (len);
}

int		get_endofline(int i, char **str, char **line)
{
	if ((!ft_strchr(*str, '\n')) && (*str == NULL))
	{
		*line = ft_strdup("");
		return (0);
	}
	else if (!ft_strchr(*str, '\n') && i == 0)
	{
		*line = *str;
		*str = NULL;
		return (0);
	}
	return (1);
}

int		get_error(int fd, char **line)
{
	if (fd < 0 || !line || BUFFER_SIZE < 0)
		return (1);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char	*str;
	size_t		len;
	char		*temp;
	int			i;

	len = 0;
	if (get_error(fd, line))
		return (-1);
	i = get_line(fd, &str);
	if (i == -1)
		return (-1);
	if ((get_endofline(i, &str, line) == 0) && i == 0)
		return (0);
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	temp = str;
	*line = ft_substr(str, 0, len);
	str = ft_strdup(temp + len + 1);
	free(temp);
	return (1);
}
