/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_open_close_check.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdibbert <fdibbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:40:45 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/16 21:22:24 by fdibbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		open_check(int fd, char ***split, char **line)
{
	if (strcmp((*split)[0], "{") == 0 && check_param_num(*split, 1))
	{
		parse_next(fd, split, line);
		return (1);
	}
	return (0);
}

int		close_check(char ***split, char **line)
{
	if (strcmp((*split)[0], "}") == 0 && check_param_num(*split, 1))
	{
		free_words(*split);
		free(*line);
		return (1);
	}
	return (0);
}
