/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_open_close_check.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdibbert <fdibbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:40:45 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/16 21:34:09 by fdibbert         ###   ########.fr       */
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

int		disruption_check(int fd, char ***split, char **line)
{
	char	**ints;

	if (strcmp((*split)[0], "disruption") == 0 && check_param_num(*split, 3))
	{
		ints = ft_strsplit((*split)[2], ' ');
		if (check_param_num(ints, 1) == 0)
			return (0);
		free_words(ints);
		parse_next(fd, split, line);
		return (1);
	}
	return (0);
}
