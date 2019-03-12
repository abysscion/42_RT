/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emayert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:22:28 by emayert           #+#    #+#             */
/*   Updated: 2018/12/05 11:22:31 by emayert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 10

# include "libft.h"
# include <unistd.h>
# include <stdio.h>

typedef	struct		s_glist
{
	struct s_glist	*next;
	char			*content;
	int				fd;
}					t_glist;

int					get_next_line(const int fd, char **line);

#endif
