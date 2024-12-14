/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hacharka <hacharka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:21:58 by hacharka          #+#    #+#             */
/*   Updated: 2024/12/14 20:11:44 by hacharka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (len > s_len - start)
		len = s_len - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if(!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	// if ((char)c == '\0')
	// 	return ((char *)&s[i]);
	return (NULL);
}
char	*ft_strdup(const char *s1)
{
	char	*copy;
	int	len;
	int	i;

	len = ft_strlen(s1);
	copy = malloc(len + 1);
	if (copy == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*read_from_file(int fd, int buffer_size)
{
	char	*buffer[buffer_size + 1];
	int		b_read;

	b_read = read(fd, buffer, buffer_size);
	buffer[b_read] = '\0';
	
	if (b_read <= 0)
		return NULL;
	else
		return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*holder;
	static char	*remaining_content;
	char	*new_read= NULL;
	int		newline_index;

	while (!ft_strchr(holder, '\n'))
	{
		new_read = read_from_file(fd, BUFFER_SIZE);

		if (new_read == NULL || new_read[0] == '\0')
			break ;
		
		holder = ft_strjoin(holder, new_read);
	}
	
	
	
}

char	*ft_strjoin(char *s1, char *s2)
{
	int	i;
	int	j;
	char	*join;

	join = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (join == NULL)
		return (NULL);
	else
	{
		i = 0;
		j = 0;
		while (i < ft_strlen(s1) && s1[i] != '\0')
		{
			join[i++] = (char)s1[j++];
		}
		j = 0;
		while (j < ft_strlen(s2) && s2[j] != '\0')
		{
			join[i++] = (char)s2[j++];
		}
		join[i] = '\0';
		free(s1);
		s1 = NULL;
		return (join);
	}
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
	printf("the content of holder : %s", rs);
	rs = get_next_line(fd);
	printf("the content of holder : %s", rs);
	return 0;
}