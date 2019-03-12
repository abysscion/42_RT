/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 11:22:28 by emayert           #+#    #+#             */
/*   Updated: 2018/12/04 13:22:31 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>

static	int		write_char(char **line, char **content)
{
	char	*tmp_content;
	char	*buf;
	int		start_pos;
	int		end_pos;

	start_pos = 0;
	end_pos = 0;
	tmp_content = *content;
	while (tmp_content[start_pos] != '\n')
		++start_pos;
	while (tmp_content[start_pos + end_pos + 1])
		++end_pos;
	if (start_pos == 0)
		*line = (char *)malloc(1);
	else
		*line = ft_strsub(*content, 0, start_pos);
	buf = *line;
	buf[start_pos] = '\0';
	buf = ft_strsub(*content, start_pos + 1, end_pos);
	free(*content);
	*content = buf;
	return (1);
}

static	int		is_eof(char **line, char **content)
{
	char	*temp;

	*line = (char *)malloc(ft_strlen(*content));
	*line = ft_strcpy(*line, *content);
	free(*content);
	*content = (char *)malloc(1);
	temp = *content;
	temp[0] = '\0';
	return (1);
}

static	int		read_buff(char **line, char **content, int fd)
{
	int		file;
	char	buff[BUFF_SIZE + 1];
	char	*temp;

	while ((file = read(fd, buff, BUFF_SIZE)))
	{
		buff[file] = '\0';
		if (!(temp = ft_strjoin(*content, &(buff[0]))))
			return (-1);
		free(*content);
		*content = temp;
		if (ft_strchr(*content, '\n'))
			return (write_char(line, content));
	}
	if (ft_strlen(*content) == 0)
		return (0);
	else
		return (is_eof(line, content));
	return (-1);
}

static	t_glist	*get_newlst(int fd)
{
	t_glist *list;

	if (!(list = (t_glist *)malloc(sizeof(t_glist))))
		return (NULL);
	list->content = (char *)malloc(1);
	list->content[0] = '\0';
	list->fd = fd;
	list->next = NULL;
	return (list);
}

int				get_next_line(const int fd, char **line)
{
	static	t_glist	*list;
	t_glist			*temp;
	char			*buf[1];

	if (!line || fd < 0 || read(fd, buf, 0) < 0)
		return (-1);
	if (list == NULL)
		list = get_newlst(fd);
	temp = list;
	while (!(temp->fd == fd))
	{
		if (temp->next == NULL)
			temp->next = get_newlst(fd);
		temp = temp->next;
	}
	if (ft_strchr(temp->content, '\n'))
		return (write_char(line, &(temp->content)));
	else
		return (read_buff(line, &(temp->content), fd));
}
