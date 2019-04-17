/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:38:08 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/17 17:50:14 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		validate_surface(int fd, int object)
{
	char	*line;
	char	**split;

	get_next_line(fd, &line);
	split = ft_strsplit(line, '\t');
	check_empty(&split, object);
	if (open_check(fd, &split, &line) == 0)
		invalid_syntax(object);
	surface_validation(split, line, object, fd);
}

static int	validate_object(int fd, int object)
{
	char	*line;
	char	**split;

	get_next_line(fd, &line);
	split = ft_strsplit(line, '\t');
	check_empty(&split, object);
	if (open_check(fd, &split, &line) == 0)
		invalid_syntax(object);
	while (1)
	{
		check_empty(&split, object);
		if (check_triple_float_field(fd, &split, &line))
			continue ;
		if (check_surface(fd, &split, &line, &object))
			continue ;
		if (close_check(&split, &line))
			break ;
		invalid_syntax(object);
	}
	return (object);
}

static void	validate_light(int fd, int object)
{
	char	*line;
	char	**split;

	get_next_line(fd, &line);
	split = ft_strsplit(line, '\t');
	check_empty(&split, object);
	if (open_check(fd, &split, &line) == 0)
		invalid_syntax(object);
	while (1)
	{
		check_empty(&split, object);
		if (check_triple_float_field(fd, &split, &line))
			continue ;
		if (intensity_check(fd, &split, &line))
			continue ;
		if (light_type_check(fd, &split, &line))
			continue ;
		if (close_check(&split, &line))
			break ;
		invalid_syntax(object);
	}
}

static void	validate_cam(int fd, int object)
{
	char	*line;
	char	**split;

	get_next_line(fd, &line);
	split = ft_strsplit(line, '\t');
	check_empty(&split, object);
	if (open_check(fd, &split, &line) == 0)
		invalid_syntax(object);
	while (1)
	{
		check_empty(&split, object);
		if (check_triple_float_field(fd, &split, &line))
			continue ;
		if (close_check(&split, &line))
			break ;
		invalid_syntax(object);
	}
}

void		parser_validation(char *name)
{
	int			fd;
	char		*line;
	char		**split;
	static int	object = 1;

	fd = open(name, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		split = ft_strsplit(line, '\t');
		check_empty(&split, object);
		if (ft_strcmp(split[0], "camera") == 0 &&
			check_param_num(split, 1))
			validate_cam(fd, object);
		else if (ft_strcmp(split[0], "light") == 0 &&
				check_param_num(split, 1))
			validate_light(fd, object);
		else if (ft_strcmp(split[0], "object") == 0 &&
				check_param_num(split, 1))
			object = validate_object(fd, object);
		else
			invalid_syntax(object);
		object++;
		free_words(split);
		free(line);
	}
	close(fd);
}
