/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 09:17:48 by saait-si          #+#    #+#             */
/*   Updated: 2025/03/18 23:19:10 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_stash(int fd, char *stash)
{
	char	*buffer;
	int		read_bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchrr(stash, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		stash = ft_strjoinn(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*return_a_line(char *stash)
{
	char	*str;
	int		i;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		str[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		str[i] = stash[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*rest_stash(char *stash)
{
	int		a;
	int		b;
	char	*string;

	a = 0;
	while (stash[a] && stash[a] != '\n')
		a++;
	if (!stash[a])
	{
		free(stash);
		return (NULL);
	}
	string = (char *)malloc(sizeof(char) * (ft_strlen(stash) - a + 1));
	if (!string)
		return (NULL);
	a++;
	b = 0;
	while (stash[a])
		string[b++] = stash[a++];
	string[b] = '\0';
	free(stash);
	return (string);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!stash)
	{
		stash = malloc(sizeof(char));
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	stash = read_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = return_a_line(stash);
	stash = rest_stash(stash);
	return (line);
}
