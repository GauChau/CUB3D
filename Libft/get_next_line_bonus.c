/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <jsaintho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 12:13:20 by gchauvot          #+#    #+#             */
/*   Updated: 2024/12/02 15:01:56 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include "libft.h"
//#define BUFFER_SIZE 3

char	*freejoin(char *res, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(res, buffer);
	free(res);
	return (temp);
}

char	*readfile(int fd, char *res)
{
	int		bytes_read;
	char	*lecture;

	if (!res)
		res = ft_calloc(1, sizeof(char));
	lecture = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!lecture)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, lecture, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(res);
			free(lecture);
			return (NULL);
		}
		lecture[bytes_read] = '\0';
		res = freejoin(res, lecture);
		if (ft_strchr(lecture, '\n'))
			break ;
	}
	free(lecture);
	return (res);
}

char	*ft_currentl(char *buffer)
{
	int		i;
	int		j;
	char	*ligne;

	i = 0;
	j = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			break ;
		i++;
	}
	ligne = ft_calloc(i + 2, sizeof(char));
	while (j < i + 1 && buffer[j] != '\0')
	{
		ligne[j] = buffer[j];
		j++;
	}
	return (ligne);
}

char	*nextline(char *buffer)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	while (buffer[i] && buffer[i] != '\n')
		i++;
	temp = ft_calloc(gnl_strlen(
				ft_strchr(buffer, '\n'), 0, 0, 1) + 1, sizeof(char));
	if (!temp)
		return (NULL);
	j = 0;
	while (buffer[i] != '\0')
	{
		i++;
		temp[j] = buffer[i];
		j++;
	}
	free(buffer);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	statik[216][BUFFER_SIZE];
	char		*buffer;
	char		*res;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
	{
		buffer = NULL;
		if (fd > -1 && read(fd, 0, 0) > -1 && statik[fd])
			ft_bzero(statik[fd], BUFFER_SIZE);
		return (buffer);
	}
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	if (statik[fd][0] != '\0')
		gnl_strlen(buffer, statik[fd], BUFFER_SIZE, 2);
	if (!ft_strchr(buffer, '\n'))
		buffer = readfile(fd, buffer);
	res = ft_currentl(buffer);
	buffer = nextline(buffer);
	if (buffer)
		gnl_strlen(statik[fd], buffer, BUFFER_SIZE, 2);
	if (buffer)
		free(buffer);
	return (res);
}
// int main(void)
// {
// 	int fd=open("read_error.txt", O_RDWR);
// 	printf("l: -%s-\n", get_next_line(fd));
// 	printf("l: -%s-\n", get_next_line(fd));
// 	printf("l: -%s-\n", get_next_line(-1));
//  close(fd);fd=open("read_error.txt", O_RDWR);
// 	printf("l: -%s-\n", get_next_line(fd));
// 	printf("l: -%s-\n", get_next_line(fd));
// 	printf("l: -%s-\n", get_next_line(fd));
// 	printf("l: -%s-\n", get_next_line(fd));
// 	printf("l: -%s-\n", get_next_line(fd));
// 	printf("l: -%s-\n", get_next_line(fd));
// 	return (0);
// }