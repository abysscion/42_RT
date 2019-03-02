/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sb_fox <xremberx@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:29:07 by cschuste          #+#    #+#             */
/*   Updated: 2019/03/01 20:55:15 by sb_fox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/rt.h"

int		main(int ac, char **av)
{
	void	*mlx;
	void	*win;
	void	*img;
	int a = -1;
	int b = 0;


	mlx = mlx_init();
	win = mlx_new_window(mlx, WIN_W, WIN_H, "Heh");
	img = mlx_xpm_file_to_image(mlx, "img/arr_right.xpm", &a, &b);
	mlx_put_image_to_window(mlx, win, img, 56, 150);
	mlx_loop(mlx);

	return (0);
}
