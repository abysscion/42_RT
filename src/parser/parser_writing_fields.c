/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_writing_fields.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 18:46:21 by eloren-l          #+#    #+#             */
/*   Updated: 2019/03/28 20:56:12 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	single_float_fields(char ***split, t_surf *surf)
{
	if (strcmp((*split)[0], "radius") == 0		||
		strcmp((*split)[0], "specular") == 0	||
		strcmp((*split)[0], "refclect") == 0	||
		strcmp((*split)[0], "transp") == 0		||
		strcmp((*split)[0], "height") == 0		||
		strcmp((*split)[0], "tip") == 0			||
		strcmp((*split)[0], "angle") == 0);
}

static void	triple_float_fields(char ***split, t_surf *surf)
{
	if (strcmp((*split)[0], "position") == 0	||
		strcmp((*split)[0], "orientation") == 0);
}

int			write_field(int fd, char ***split, char **line, t_surf *surf)
{
	char	**num;

	num = ft_strsplit((*split)[2], ' ');
	if (check_param_num(num, 1))
		single_float_fields(split, surf);
	else if (check_param_num(num, 3))
		triple_float_fields(split, surf);
	free_words(num);
	free_words(*split);
	free(*line);
	get_next_line(fd, line);
	*split = ft_strsplit(*line, "\t");
}