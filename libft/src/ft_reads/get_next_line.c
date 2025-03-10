/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstoev <sstoev@student.42malaga.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 20:47:30 by sstoev            #+#    #+#             */
/*   Updated: 2024/10/06 20:47:35 by sstoev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_to_buffer(int fd, char *res);
char	*ft_strjoin_free(char *res, char *buffer_temp);
char	*ft_get_line(char *buffer);
char	*ft_get_residual_buffer(char *buffer);

char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read_to_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_get_line(buffer);
	if (!line)
		return (free(buffer), buffer = NULL, NULL);
	buffer = ft_get_residual_buffer(buffer);
	return (line);
}

char	*ft_read_to_buffer(int fd, char *res)
{
	char	*buffer_temp;
	int		bytes_read;

	if (!res)
		res = ft_calloc(1, 1);
	buffer_temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer_temp)
		return (free(res), res = NULL, NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer_temp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer_temp);
			free(res);
			return (buffer_temp = NULL, res = NULL, NULL);
		}
		buffer_temp[bytes_read] = '\0';
		res = ft_strjoin_free(res, buffer_temp);
		if (res && ft_strchr(res, '\n'))
			break ;
	}
	free(buffer_temp);
	return (res);
}

char	*ft_strjoin_free(char *res, char *buffer_temp)
{
	char	*new_res;

	new_res = ft_strjoin(res, buffer_temp);
	free(res);
	res = NULL;
	return (new_res);
}

char	*ft_get_line(char *buffer)
{
	char		*line;
	size_t		i;

	if (!buffer[0])
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc((i + 1), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*ft_get_residual_buffer(char *buffer)
{
	char		*buffer_residual;
	size_t		i;
	size_t		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer && !buffer[i])
		return (free(buffer), buffer = NULL, NULL);
	i++;
	buffer_residual = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!buffer_residual)
		return (free(buffer), buffer = NULL, NULL);
	j = 0;
	while (buffer[i])
		buffer_residual[j++] = buffer[i++];
	free(buffer);
	return (buffer_residual);
}
/*
#include <string.h>

int	main(void)
{
	int		fd;


	fd = open("test",O_RDONLY);
	
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
	close(fd);

	return (0);
}
*/
/*
int	main(void)
{
	int		fd;

// Test--- file input
	fd = open("test",O_RDONLY);

	printf("Test1: %s\n", get_next_line(fd)); // expects NULL
	printf("Test2: %s\n", get_next_line(fd)); // expects NULL
	printf("Test3: %s\n", get_next_line(fd)); // expects NULL
	printf("Test4: %s\n", get_next_line(fd)); // expects NULL

	close(fd);
	return (0);
}
*/
/*
int	main(void)
{
	int		fd;

// Test--- file input
	fd = open("test",O_RDONLY);

	printf("Test1: %s", get_next_line(fd)); // expect "aa...\n"
	printf("Test2: %s", get_next_line(fd)); // expect "bb...\n"
	
	// Introduce error
	introduced_error = 1;
	printf("Test3: %s", get_next_line(fd)); // expect NULL
	close(fd);
	printf("\n");
	
	// Reset and re-read
	introduced_error = 0;
	fd = open("test",O_RDONLY);
	printf("Test4: %d\n", strcmp(get_next_line(fd),"aaaaaaaaaa\n"));
	printf("Test5: %d\n", strcmp(get_next_line(fd),"bbbbbbbbbb\n"));
	printf("Test6: %d\n", strcmp(get_next_line(fd),"cccccccccc\n"));
	printf("Test7: %d\n", strcmp(get_next_line(fd),"dddddddddd\n"));

	close(fd);
	return (0);
}
*/
/*
int	main(void)
{
	int		fd;
	char	*t_line;
	//char	*stdin_line;

// Test--- file input
	fd = open("test",O_RDONLY);
	printf("%s\n", "---reading the whole file till EOL---");
	while ((t_line = get_next_line(fd)))
	{
		printf("%s", t_line);
		free(t_line);
	}
	close(fd);
	fd = open("test",O_RDONLY);
	printf("\n");

	printf("%s\n", "---Trying to read again---");
	t_line = get_next_line(fd);
	printf("%s", t_line);
	printf("%s\n", "---And again---");
	t_line = get_next_line(fd);
	printf("%s", t_line);
	free(t_line);


// Test--- standard input
	while ((stdin_line = get_next_line(0)))
	{
		printf("%s", stdin_line);
		free(stdin_line);
	}

	return (0);
}
*/