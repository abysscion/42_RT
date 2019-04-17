/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_open_close_check.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:40:45 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/17 17:25:29 by eloren-l         ###   ########.fr       */
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

void	check_empty(char ***split, int object)
{
	if (*split[0] == NULL)
		invalid_syntax(object);
}

void	surface_validation(char **split, char *line, int object, int fd)
{
	while (1)
	{
		check_empty(&split, object);
		if (check_single_float_field(fd, &split, &line))
			continue ;
		if (check_triple_float_field(fd, &split, &line))
			continue ;
		if (color_check(fd, &split, &line))
			continue ;
		if (texture_check(fd, &split, &line))
			continue ;
		if (surface_type_check(fd, &split, &line))
			continue ;
		if (disruption_check(fd, &split, &line))
			continue ;
		if (close_check(&split, &line))
			break ;
		invalid_syntax(object);
	}
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
