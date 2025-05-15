/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:55:36 by esellier          #+#    #+#             */
/*   Updated: 2024/10/04 16:00:29 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>

char	*ft_stach_error(char **stach)
{
	if (*stach)
	{
		free (*stach);
		*stach = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*stach[1024 + 1];
	int			readed;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 1)
		return (NULL);
	if (ft_search_line((stach[fd])))
		return (ft_end_stach(&(stach[fd])));
	buf = malloc(BUFFER_SIZE * sizeof(char));
	if (!buf)
		return (ft_stach_error(&(stach[fd])));
	readed = read(fd, buf, BUFFER_SIZE);
	if (readed > 0)
	{
		ft_buf_cpy(&(stach[fd]), buf, readed);
		free (buf);
		if (!stach[fd])
			return (NULL);
		return (get_next_line(fd));
	}
	free (buf);
	if (readed < 0 || !stach[fd] || ft_strlen_gnl(stach[fd], 0) == 0)
		return (ft_stach_error(&(stach[fd])));
	return (ft_sub_stach(&(stach[fd]), 0));
}

/*#include <fcntl.h>

int	main()
{
	int		fd;
	char	*line;
	int		fd2;

	fd = open("test.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		printf("text2:%s", get_next_line(fd2));
		if(line == NULL)
			return (0);
		printf("text1:%s", line);
		free(line);
	}
	return (0);
}*/