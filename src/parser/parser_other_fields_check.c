/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_other_fields_check.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 16:22:22 by eloren-l          #+#    #+#             */
/*   Updated: 2019/03/28 19:59:14 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		texture_check(int fd, char ***split, char **line)
{
	char **texture;

	if (strcmp((*split)[0], "texture") == 0 && check_param_num(*split, 3))
	{
		texture = ft_strsplit((*split)[2], ' ');
		if (check_param_num(texture, 1) == 0)
			return (0);
		free_words(texture);
		parse_next(fd, split, line);
		return (1);
	}
	return (0);
}

int		intensity_check(int fd, char ***split, char **line)
{
	char	**floats;

	if (strcmp((*split)[0], "intensity") == 0 && check_param_num(*split, 3))
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

int		color_check(int fd, char ***split, char **line)
{
	char	**ints;

	if (strcmp((*split)[0], "color") == 0 && check_param_num(*split, 3))
	{
		ints = ft_strsplit((*split)[2], ' ');
		if (check_param_num(ints, 3) == 0)
			return (0);
		free_words(ints);
		parse_next(fd, split, line);
		return (1);
	}
	return (0);
}

int		light_type_check(int fd, char ***split, char **line)
{
	int		flag;

	flag = 0;
	if (strcmp((*split)[0], "type") == 0 && check_param_num(*split, 3))
	{
		if (strcmp((*split)[2], "AMBIENT") == 0)
			flag = T_AMBIENT;
		if (strcmp((*split)[2], "POINT") == 0)
			flag = T_POINT;
		if (strcmp((*split)[2], "DIRECTIONAL") == 0)
			flag = T_DIRECTIONAL;
		parse_next(fd, split, line);
		return(flag);
	}
	return (0);
}

int		surface_type_check(int fd, char ***split, char **line)
{
	int		flag;

	flag = 0;
	if (strcmp((*split)[0], "type") == 0 && check_param_num(*split, 3))
	{
		if (strcmp((*split)[2], "SPHERE") == 0)
			flag = T_SPHERE;
		if (strcmp((*split)[2], "CONE") == 0)
			flag = T_CONE;
		if (strcmp((*split)[2], "CYLINDER") == 0)
			flag = T_CYLINDER;
		if (strcmp((*split)[2], "PLANE") == 0)
			flag = T_PLANE;
		parse_next(fd, split, line);
		return(flag);
	}
	return (0);
}