/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_open_close_check.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:40:45 by eloren-l          #+#    #+#             */
/*   Updated: 2019/03/28 19:56:20 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			open_check(int fd, char ***split, char **line)
{	
	if (strcmp((*split)[0], "{") == 0 && check_param_num(*split, 1))
	{
		parse_next(fd, split, line);
		return (1);
	}
	return (0);
}

int		close_check(int fd, char ***split, char **line)
{
	if (strcmp((*split)[0], "}") == 0 && check_param_num(*split, 1))
	{
		free_words(*split);
		free(*line);
		return (1);
	}
	return (0);
}
