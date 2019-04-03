/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_float_fields_check.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:03:55 by eloren-l          #+#    #+#             */
/*   Updated: 2019/03/30 14:09:24 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	single_float_fields(char ***split)
{
	if (strcmp((*split)[0], "radius") == 0 ||
		strcmp((*split)[0], "specular") == 0 ||
		strcmp((*split)[0], "reflect") == 0 ||
		strcmp((*split)[0], "transp") == 0 ||
		strcmp((*split)[0], "height") == 0 ||
		strcmp((*split)[0], "tip") == 0 ||
		strcmp((*split)[0], "angle") == 0)
		return (1);
	return (0);
}

static int	triple_float_fields(char ***split)
{
	if (strcmp((*split)[0], "position") == 0 ||
		strcmp((*split)[0], "orientation") == 0)
		return (1);
	return (0);
}

int			check_single_float_field(int fd, char ***split, char **line)
{
	char	**floats;

	if (check_param_num(*split, 3) && single_float_fields(split))
	{
		floats = ft_strsplit((*split)[2], ' ');
		if (check_param_num(floats, 1) == 0)
			return (0);
		if (check_floats(floats, 1) == 0)
			return (0);
		free_words(floats);
		parse_next(fd, split, line);
		return (1);
	}
	return (0);
}

int			check_triple_float_field(int fd, char ***split, char **line)
{
	char	**floats;

	if (check_param_num(*split, 3) && triple_float_fields(split))
	{
		floats = ft_strsplit((*split)[2], ' ');
		if (check_param_num(floats, 3) == 0)
			return (0);
		if (check_floats(floats, 3) == 0)
			return (0);
		free_words(floats);
		parse_next(fd, split, line);
		return (1);
	}
	return (0);
}

int			check_surface(int fd, char ***split, char **line, int *object)
{
	if (strcmp((*split)[0], "surface") == 0 && check_param_num(*split, 1))
	{
		(*object)++;
		validate_surface(fd, *object);
		parse_next(fd, split, line);
		return (1);
	}
	return (0);
}
