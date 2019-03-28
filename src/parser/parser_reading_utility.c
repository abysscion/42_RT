/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_reading_utility.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eloren-l <eloren-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:22:32 by eloren-l          #+#    #+#             */
/*   Updated: 2019/03/28 19:54:46 by eloren-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_next(int fd, char ***split, char **line)
{
	free_words(*split);
	free(*line);
	get_next_line(fd, line);
	*split = ft_strsplit(*line, "\t");
}

void		invalid_syntax(int object)
{
	ft_putstr("syntax error or wrong field in structure # ");
	ft_putstr(ft_itoa(object));
	ft_putstr("\nexiting\n");
	exit(0);
}

int			check_param_num(char **param, int i)
{
	int		j;

	j = 0;
	while (*param)
	{
		param++;
		j++;
	}
	if (i == j)
		return (1);
	return (0);
}

int			check_floats(char **param, int i)
{
	char	**num;
	int		j;

	j = 0;
	while (j < i)
	{
		num = ft_strsplit(param[j++], '.');
		if (check_param_num(num, 2) == 0)
			return (0);
		free_words(num);
	}
	return(1);
}

void		free_words(char **words)
{
	int		i;

	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
}
