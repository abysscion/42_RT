/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:38:08 by eloren-l          #+#    #+#             */
/*   Updated: 2019/03/28 16:30:42 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		validate_surface(int fd, int object)
{
	char	*line;
	char	**split;

	get_next_line(fd, &line);
	split = ft_strsplit(line, '\t');
	while (1)
	{
		if (open_check(fd, &split, &line))
			continue ;
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
		if (close_check(fd, &split, &line))
			break ;
		invalid_syntax(object);
	}
}

static int	validate_object(int fd, int object)
{
	char	*line;
	char	**split;

	get_next_line(fd, &line);
	split = ft_strsplit(line, '\t');
	while (1)
	{
		if (open_check(fd, &split, &line))
			continue ;
		if (check_triple_float_field(fd, &split, &line))
			continue ;
		if (check_surface(fd, &split, &line, &object));
			continue ;
		if (close_check(fd, &split, &line))
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
	while (1)
	{
		if (open_check(fd, &split, &line))
			continue ;
		if (check_triple_float_field(fd, &split, &line))
			continue ;
		if (intentsity_check(fd, &split, &line))
			continue ;
		if (light_type_check(fd, &split, &line))
			continue ;
		if (close_check(fd, &split, &line))
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
	while (1)
	{
		if (open_check(fd, &split, &line))
			continue ;
		if (check_triple_float_field(fd, &split, &line))
			continue ;
		if (close_check(fd, &split, &line))
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
		free_word(split);
		free(line);
	}
}
