/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: final-one <final-one@student.42seoul.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 14:02:50 by jonchoi           #+#    #+#             */
/*   Updated: 2022/08/25 04:17:16 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*ft_lstnew(int fd, t_list **head);
char	*read_buf(int fd, t_list *node);
void	free_node(int fd, t_list **head);
char	*split_line(char *line);

char	*get_next_line(int fd)
{
	static t_list	*list;
	t_list			*node;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = list;
	while (node)
	{
		if (node->fd == fd)
			break ;
		node = node->next;
	}
	if (!node)
		node = ft_lstnew(fd, &list);
	line = read_buf(fd, node);
	node->backup = NULL;
	if (!line)
	{
		free_node(fd, &list);
		return (NULL);
	}
	node->backup = split_line(line);
	return (line);
}

t_list	*ft_lstnew(int fd, t_list **head)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (0);
	new->fd = fd;
	new->backup = NULL;
	new->next = *head;
	*head = new;
	return (new);
}

char	*read_buf(int fd, t_list *node)
{
	char	*temp;
	int		num;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (1)
	{
		num = read(fd, buf, BUFFER_SIZE);
		if (num <= 0)
			break ;
		buf[num] = '\0';
		if (!(node->backup))
			node->backup = ft_strdup("");
		temp = node->backup;
		node->backup = ft_strjoin(temp, buf);
		free(temp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (node->backup);
}

void	free_node(int fd, t_list **head)
{
	t_list	*temp;
	t_list	*start_add;

	if ((*head)->fd == fd)
	{
		temp = (*head);
		(*head) = (*head)->next;
		free(temp);
	}
	else
	{
		start_add = *head;
		while ((*head)->next->fd != fd)
			(*head) = (*head)->next;
		temp = (*head)->next;
		(*head)->next = (*head)->next->next;
		free(temp);
		*head = start_add;
	}
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
