/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_writing_fields.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 18:46:21 by eloren-l          #+#    #+#             */
/*   Updated: 2019/04/17 19:42:49 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	single_num_fields(char ***split, char **num, t_surf *surf)
{
	if (strcmp((*split)[0], "radius") == 0)
		surf->radius = ft_atod(num[0]);
	else if (strcmp((*split)[0], "specular") == 0)
		surf->specular = ft_atod(num[0]);
	else if (strcmp((*split)[0], "reflect") == 0)
		surf->reflect = ft_atod(num[0]);
	else if (strcmp((*split)[0], "transp") == 0)
		surf->transp = ft_atod(num[0]);
	else if (strcmp((*split)[0], "max_height") == 0)
		surf->limits.max_height = ft_atod(num[0]);
	else if (strcmp((*split)[0], "min_height") == 0)
		surf->limits.min_height = ft_atod(num[0]);
	else if (strcmp((*split)[0], "max_width") == 0)
		surf->limits.max_width = ft_atod(num[0]);
	else if (strcmp((*split)[0], "min_width") == 0)
		surf->limits.min_width = ft_atod(num[0]);
	else if (strcmp((*split)[0], "angle") == 0)
		surf->radius = ft_atod(num[0]);
	else if (strcmp((*split)[0], "refract") == 0)
		surf->refract = ft_atod(num[0]);
	else if (strcmp((*split)[0], "disruption") == 0)
		surf->disruption = ft_atoi(num[0]);
}

static void	triple_num_fields(char ***split, char **num, t_surf *surf)
{
	if (strcmp((*split)[0], "position") == 0)
		surf->position_init = (t_v){ft_atod(num[0]),
			ft_atod(num[1]), ft_atod(num[2])};
	else if (strcmp((*split)[0], "rotation") == 0)
		surf->rotation_init = (t_v){ft_atod(num[0]),
			ft_atod(num[1]), ft_atod(num[2])};
	else if (strcmp((*split)[0], "color") == 0)
		surf->color = (t_clr){ft_atoi(num[0]),
			ft_atoi(num[1]), ft_atoi(num[2])};
}

void		write_field(int fd, char ***split, char **line, t_surf *surf)
{
	char	**num;

	num = ft_strsplit((*split)[2], ' ');
	if (check_param_num(num, 1))
		single_num_fields(split, num, surf);
	else if (check_param_num(num, 3))
		triple_num_fields(split, num, surf);
	free_words(num);
	parse_next(fd, split, line);
}
