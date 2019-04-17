/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:33:38 by fdibbert          #+#    #+#             */
/*   Updated: 2019/04/17 19:52:50 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		check_filename(char *file_name)
{
	int fd;
	char	*line;

	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		ft_putstr("Wrong file\n");
		exit(0);
	}
	close(fd);
	fd = open(file_name, O_RDONLY);
	if (get_next_line(fd, &line) == 0)
	{
		ft_putstr("Wrong file\n");
		exit(0);
	}
	close(fd);
}
