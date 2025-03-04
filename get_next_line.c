/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plantsov <plantsov@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:50:35 by plantsov          #+#    #+#             */
/*   Updated: 2025/03/04 16:53:06 by plantsov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_buffer(int fd, char **text_buffer, char *buffer)
{
	char	*temp;
	int		read_size;

	read_size = read(fd, buffer, BUFFER_SIZE);
	while (read_size > 0)
	{
		buffer[read_size] = '\0';
		if (!*text_buffer)
			*text_buffer = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(*text_buffer, buffer);
			free(*text_buffer);
			*text_buffer = temp;
		}
		if (ft_strchr(*text_buffer, '\n'))
			break ;
		read_size = read(fd, buffer, BUFFER_SIZE);
	}
	return (read_size);
}

static char	*upd_buffer(char *buffer, int ln_len)
{
	char	*temp;

	temp = ft_strdup(buffer + ln_len + 1);
	free(buffer);
	if (!*temp)
	{
		free(temp);
		return (NULL);
	}
	return (temp);
}

static char	*pull_line(char *buffer, int ln_len)
{
	char	*ln;
	int		i;

	ln = malloc((ln_len + 2) * sizeof(char));
	if (!ln)
		return (NULL);
	i = 0;
	while (i <= ln_len)
	{
		ln[i] = buffer[i];
		i++;
	}
	ln[i] = '\0';
	return (ln);
}

static char	*get_line(char **text_buffer)
{
	char	*ln;
	int		i;

	i = 0;
	while ((*text_buffer)[i] && (*text_buffer)[i] != '\n')
		i++;
	if ((*text_buffer)[i] == '\n')
	{
		ln = pull_line(*text_buffer, i);
		*text_buffer = upd_buffer(*text_buffer, i);
	}
	else
	{
		ln = ft_strdup(*text_buffer);
		free(*text_buffer);
		*text_buffer = NULL;
	}
	return (ln);
}

char	*get_next_line(int fd)
{
	static char	*text_buffer;
	char		*buffer;
	char		*result;
	int			read_size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_size = read_buffer(fd, &text_buffer, buffer);
	free(buffer);
	if (read_size < 0 || (read_size == 0 && !text_buffer))
		return (NULL);
	result = get_line(&text_buffer);
	return (result);
}