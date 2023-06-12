/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 09:51:25 by jonchoi           #+#    #+#             */
/*   Updated: 2022/08/25 04:22:57 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_buf(int fd, char *p_backup);
char	*split_line(char *line);

char	*get_next_line(int fd)
{
	char		*line;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_buf(fd, backup);
	backup = NULL;
	if (!line)
		return (NULL);
	backup = split_line(line);
	return (line);
}

char	*read_buf(int fd, char *p_backup)
{
	char	*buf;
	char	*temp;
	int		num;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (1)
	{
		num = read(fd, buf, BUFFER_SIZE);
		if (num <= 0)
			break ;
		buf[num] = '\0';
		if (!p_backup)
			p_backup = ft_strdup("");
		temp = p_backup;
		p_backup = ft_strjoin(temp, buf);
		free(temp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (p_backup);
}

char	*split_line(char *line)
{
	char	*update;
	int		idx;

	idx = 0;
	while (line[idx] != '\n' && line[idx] != '\0')
		idx++;
	if (line[idx] == '\0')
		return (NULL);
	update = ft_substr(line, idx + 1, ft_strlen(line) - idx - 1);
	if (update[0] == '\0')
	{
		free(update);
		return (NULL);
	}
	line[idx + 1] = '\0';
	return (update);
}
