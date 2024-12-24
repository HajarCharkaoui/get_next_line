/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hacharka <hacharka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:27:55 by hacharka          #+#    #+#             */
/*   Updated: 2024/12/24 15:51:29 by hacharka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*set_line(char *s)
{
	int		i;
	int		j;
	char	*lign;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	lign = malloc(i + 1);
	if (!lign)
		return (NULL);
	j = 0;
	while (j < i)
	{
		lign[j] = s[j];
		j++;
	}
	lign[j] = '\0';
	return (lign);
}

char	*remaining_content(char *s)
{
	int		i;
	int		j;
	char	*aftrline;

	i = 0;
	j = 1;
	if (!s)
		return (NULL);
	while (s[i] && j != 0)
	{
		if (s[i] == '\n')
			j = 0;
		i++;
	}
	aftrline = malloc(ft_strlen(s) - i + 1);
	if (!aftrline)
		return (NULL);
	j = 0;
	while (s[i])
		aftrline[j++] = s[i++];
	aftrline[j] = '\0';
	free(s);
	return (aftrline);
}

char	*read_from_file(int fd, char *buffer)
{
	char	*holder;
	int		bytes_read;

	holder = (char *)malloc(BUFFER_SIZE + 1);
	if (!holder)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, holder, BUFFER_SIZE);
		if (bytes_read < 0 || (bytes_read == 0 && (!buffer || !*buffer)))
			return (free(buffer), free(holder), NULL);
		holder[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, holder);
	}
	free(holder);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_from_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = set_line(buffer[fd]);
	buffer[fd] = remaining_content(buffer[fd]);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// char	*get_next_line(int fd);

// int	main(void)
// {
// 	int fd1 = open("file1.txt", O_RDONLY);
// 	int fd2 = open("file2.txt", O_RDONLY);
// 	int fd3 = open("hajar.txt", O_RDONLY);
// 	char *line1 = NULL;
// 	char *line2 = NULL;
// 	char *line3 = NULL;

// 	printf("fd1: %d, fd2: %d, fd3: %d\n", fd1, fd2, fd3);

// 	if (fd1 < 0)
// 	{
// 		perror("Error opening file1.txt");
// 		return (1);
// 	}

// 	if (fd2 < 0)
// 	{
// 		perror("Error opening file2.txt");
// 		close(fd1);
// 		return (1);
// 	}
// 	if (fd3 < 0)
// 	{
// 		perror("Error opening hajar.txt");
// 		close(fd2);
// 		return (1);
// 	}

// 	line1 = get_next_line(fd1);
// 	if (line1)
// 	{
// 		printf("file1: %s\n", line1);
// 		free(line1);
// 	}
// 	else
// 	{
// 		printf("file1: (null)\n");
// 	}
// 	line1 = get_next_line(fd1);
// 	if (line1)
// 	{
// 		printf("file1: %s\n", line1);
// 		free(line1);
// 	}
// 	else
// 	{
// 		printf("file1: (null)\n");
// 	}

// 	line2 = get_next_line(fd2);
// 	if (line2)
// 	{
// 		printf("file2: %s\n", line2);
// 		free(line2);
// 	}
// 	else
// 	{
// 		printf("file2: (null)\n");
// 	}
// 	line3 = get_next_line(fd3);
// 	if (line3)
// 	{
// 		printf("file3: %s\n", line3);
// 		free(line3);
// 	}
// 	else
// 	{
// 		printf("file3: (null)\n");
// 	}

// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }