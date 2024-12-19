/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hacharka <hacharka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:21:58 by hacharka          #+#    #+#             */
/*   Updated: 2024/12/19 18:16:59 by hacharka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		end_of_line(char *s, int c)
{
	int	i;

	i = 0;
	if(!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			break ;
		}
		i++;
	}
	return (i);
}

void	free_holder(char **holder)
{
	if (*holder)
	{
		free(*holder);
		*holder = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*holder;
	char	*line ;
	char	*rst;
	char	*buffer;
	int		b_read;
	
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	b_read  = 1;
	while (b_read > 0 && !ft_strchr(buffer, '\n'))
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read < 0)
		{
			free(buffer);
			return (NULL);
		} 
		buffer[b_read] = '\0';
		holder = ft_strjoin(holder, buffer);
	}
	free(buffer);
	line = ft_substr(holder, 0, end_of_line(holder, '\n') + 1);
	rst = ft_substr(holder, end_of_line(holder, '\n') + 1, ft_strlen(holder) - (end_of_line(holder, '\n') + 1));
	holder = rst;
	return (line);
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
// 	// free(rs);
// 	// printf("the content of holder : {%s}\n", rs);
// 	rs = get_next_line(fd);
// 	printf(" second call the content of holder : %s\n", rs);
// 	rs = get_next_line(fd);
// 	printf(" third call the content of holder : %s\n", rs);
// 	rs = get_next_line(fd);
// 	printf(" 4 call the content of holder : %s\n", rs);
// 	rs = get_next_line(fd);
// 	printf(" 5 call the content of holder : %s\n", rs);
// 	rs = get_next_line(fd);
// 	printf(" 6 call the content of holder : %s\n", rs);
// 	return 0;
// }