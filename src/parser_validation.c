/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:38:08 by eloren-l          #+#    #+#             */
/*   Updated: 2019/03/24 20:38:57 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** add parser validation for texture name and it's existence
*/

static void	validate_surface(char **params, char *name)
{
	char	**split;

	check_param_num(params, 10, name);
	check_floats(&params[4], 1, name);
	check_floats(&params[5], 1, name);
	check_floats(&params[6], 1, name);
	check_floats(&params[7], 1, name);
	check_floats(&params[8], 1, name);
	split = ft_strsplit(params[1], ',');
	check_param_num(split, 3, name);
	free_words(split);
	split = ft_strsplit(params[2], ',');
	check_param_num(split, 3, name);
	check_floats(split, 3, name);
	free_words(split);
	split = ft_strsplit(params[2], ',');
	check_param_num(split, 3, name);
	check_floats(split, 3, name);
	free_words(split);
	free_words(params);
}

static void	validate_light(char **params)
{
	char	**coords;

	check_param_num(params, 4, "light");
	coords = ft_strsplit(params[1], ',');
	check_param_num(coords, 3, "light");
	check_floats(coords, 3, "light");
	check_floats(&params[2], 1, "light");
	free_words(coords);
	free_words(params);
}

static void	validate_cam(char **params)
{
	char	**coords;

	check_param_num(params, 3, "camera");
	coords = ft_strsplit(params[1], ',');
	check_param_num(coords, 3, "camera");
	check_floats(coords, 3, "camera");
	free_words(coords);
	coords = ft_strsplit(params[2], ',');
	check_param_num(coords, 3, "camera");
	check_floats(coords, 3, "camera");
	free_words(coords);
	free(params);
}

static void	select_function(char **params)
{
	if (ft_strcmp(params[0], "camera") == 0)
		validate_cam(params);
	else if (ft_strcmp(params[0], "light") == 0)
		validate_light(params);
	else if (ft_strcmp(params[0], "sphere") == 0)
		validate_surface(params, "sphere");
	else if (ft_strcmp(params[0], "plane") == 0)
		validate_surface(params, "plane");
	else if (ft_strcmp(params[0], "cylinder") == 0)
		validate_surface(params, "cylinder");
	else if (ft_strcmp(params[0], "cone") == 0)
		validate_surface(params, "cone");
	else
	{
		ft_putstr("Wrong object name. Exiting.\n");
		exit(0);
	}
}

void		parser_validation(char *name)
{
	int		fd;
	char	*line;
	char	**split;

	fd = open(name, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		split = ft_strsplit(line, '\t');
		select_function(split);
		free(line);
	}
}
