/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 19:15:03 by patrisor          #+#    #+#             */
/*   Updated: 2019/05/29 16:59:30 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * Print how-to use instructions
 */
void	print_menu(t_mlx *lib)
{
	int		y;
	void	*mlx;
	void	*win;

	y = 0;
	mlx = lib->mlx;
	win = lib->window;
	mlx_string_put(mlx, win, 65, y += 25, TEXT_COLOR, "How to Use:");
	mlx_string_put(mlx, win, 15, y += 25, TEXT_COLOR, "Zoom: Hold right mouse & Move");
	mlx_string_put(mlx, win, 15, y += 25, TEXT_COLOR, "Move: W, A, S, D");
	mlx_string_put(mlx, win, 15, y += 25, TEXT_COLOR, "Rotate: Hold left mouse & Move");
	mlx_string_put(mlx, win, 15, y += 25, TEXT_COLOR, "Colors: Arrow Keys");
	mlx_string_put(mlx, win, 15, y += 25, TEXT_COLOR, "Exit: ESC");
}
