/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hacharka <hacharka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:21:58 by hacharka          #+#    #+#             */
/*   Updated: 2024/12/17 14:09:43 by hacharka         ###   ########.fr       */
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

char	*read_from_file(int fd, int buffer_size)
{
	char	*buffer;
	int		b_read;

	buffer = malloc(buffer_size + 1);
	if (buffer == NULL)
		return (NULL);
	b_read  = 0;
	b_read = read(fd, buffer, buffer_size);
	if (b_read <= 0)
	{
		free(buffer);
		return NULL;
	}	
	buffer[b_read] = '\0';
	return (buffer);
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
	char	*holder = NULL;
	static char	*remaining_content = NULL;
	char	*line = NULL;
	char	*new_read= NULL;
	int		newline_index;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!ft_strchr(holder, '\n'))
	{
		new_read = read_from_file(fd, BUFFER_SIZE);
		if (new_read == NULL || new_read[0] == '\0')
		{
			free(new_read);
			break ;
		}	
		holder = ft_strjoin(holder, new_read);
		free(new_read);
		if (remaining_content != NULL)
		{
			holder = ft_strjoin(remaining_content, holder);
			free(remaining_content);
			remaining_content = NULL;
		}
	}
	if (holder)
	{
		newline_index = 0;
		newline_index = end_of_line(holder, '\n');
		line = ft_substr(holder, 0, newline_index);
		remaining_content = ft_substr(holder, newline_index + 1, ft_strlen(holder));
		free_holder(&holder);
	}
	return (line);
}

#include <stdio.h>
#include <fcntl.h>

int main()
{
	char *rs = NULL;
	int fd = open("hajar.txt", O_RDONLY);

	if (fd < 0)
		return 1;
	rs = get_next_line(fd);
	printf("the content of holder : {%s}\n", rs);
	rs = get_next_line(fd);
	printf(" second call the content of holder : %s\n", rs);
	rs = get_next_line(fd);
	printf(" third call the content of holder : %s\n", rs);
	rs = get_next_line(fd);
	printf(" 4 call the content of holder : %s\n", rs);
	return 0;
}