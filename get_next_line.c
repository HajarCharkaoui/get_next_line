/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hacharka <hacharka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:21:58 by hacharka          #+#    #+#             */
/*   Updated: 2024/12/23 22:10:43 by hacharka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_from_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = set_line(buffer);
	buffer = remaining_content(buffer);
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>

// int main()
// {
// 	char *rs = NULL;
// 	int fd = open("hajar.txt", O_RDONLY);

// 	if (fd < 0)
// 		return (1);
// 	rs = get_next_line(fd);
// 	write(1, rs, ft_strlen(rs));
// 	free(rs);
// // 	// // printf("the content of holder : {%s}\n", rs);
// 	rs = get_next_line(fd);
// 	printf(" second call the content of holder : {%s}\n", rs);
// 	free(rs);
// // 	// rs = get_next_line(fd);
// // 	// printf(" third call the content of holder : %s\n", rs);
// // 	// free(rs);
// // 	// rs = get_next_line(fd);
// // 	// printf(" 4 call the content of holder : %s\n", rs);
// // 	// free(rs);
// // 	// rs = get_next_line(fd);
// // 	// printf(" 5 call the content of holder : %s\n", rs);
// // 	// free(rs);
// // 	// rs = get_next_line(fd);
// // 	// printf(" 6 call the content of holder : %s\n", rs);
// // 	// free(rs);
// // 	// rs = get_next_line(fd);
// // 	// printf(" 7 call the content of holder : %s\n", rs);
// // 	// free(rs);
// // 	// 	rs = get_next_line(fd);
// // 	// printf(" 8 call the content of holder : %s\n", rs);
// // 	// free(rs);
// 	close(fd);
// 	return (0);
// }