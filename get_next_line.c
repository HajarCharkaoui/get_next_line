/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hacharka <hacharka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:21:58 by hacharka          #+#    #+#             */
/*   Updated: 2024/12/22 21:23:15 by hacharka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*set_line(char *buffer)
{
	char	*line;
	int		l;
	int		i;

	l = 0;
	if (buffer[l] == '\0')
	return (NULL);
	while (buffer[l] && buffer[l] != '\n')
	l++;
	if (buffer[l] == '\n')
	l++;
	line = (char *)malloc(l + 1);
	if (!line)
	return (NULL);
	i = 0;
	while (i < l)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*remaining_content(char *buff)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	if (!buff)
	return (NULL);
	while (buff[i] && buff[i] != '\n')
	i++;
	if (buff[i] == '\n')
	i++;
	if (i == (int)ft_strlen(buff))
	{
		free(buff);
		return (NULL);
	}
	rest = (char *)malloc(ft_strlen(buff) - i + 1);
	if (!rest)
	return (NULL);
	j = 0;
	while (buff[i])
	rest[j++] = buff[i++];
	rest[j] = '\0';
	free(buff);
	return (rest);
	
}


char *get_next_line(int fd)
{
	static char	*buff;
	char	*buffer;
	char	*line;
	char	*remaining;
	int		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	bytes_read = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	while (bytes_read > 0 && ft_strchr(buff, '\n') == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buff);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		buff = ft_strjoin(buff, buffer);
	}
	free(buffer);
	line = set_line(buff);
	remaining = remaining_content(buff);
	buff = remaining;
	return line;
}

// #include <stdio.h>
// #include <fcntl.h>

// int main()
// {
// 	char *rs = NULL;
// 	int fd = open("hajar.txt", O_RDONLY);

// 	if (fd < 0)
// 		return 1;
// 	rs = get_next_line(fd);
// 	printf("first read : {%s}\n", rs);
// 	free(rs);
// // 	// // printf("the content of holder : {%s}\n", rs);
// 	// rs = get_next_line(fd);
// 	// printf(" second call the content of holder : {%s}\n", rs);
// 	// free(rs);
// 	// rs = get_next_line(fd);
// 	// printf(" third call the content of holder : %s\n", rs);
// 	// free(rs);
// 	// rs = get_next_line(fd);
// 	// printf(" 4 call the content of holder : %s\n", rs);
// 	// free(rs);
// 	// rs = get_next_line(fd);
// 	// printf(" 5 call the content of holder : %s\n", rs);
// 	// free(rs);
// 	// rs = get_next_line(fd);
// 	// printf(" 6 call the content of holder : %s\n", rs);
// 	// free(rs);
// 	// rs = get_next_line(fd);
// 	// printf(" 7 call the content of holder : %s\n", rs);
// 	// free(rs);
// 	// 	rs = get_next_line(fd);
// 	// printf(" 8 call the content of holder : %s\n", rs);
// 	// free(rs);
// 	close(fd);
// 	return 0;
// }