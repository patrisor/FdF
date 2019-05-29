/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 21:16:46 by patrisor          #+#    #+#             */
/*   Updated: 2019/05/29 00:08:58 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * Key code for W, A, S, D to control panning effect
 */
void	move(int key, t_mlx *mlx)
{
	if (key == KEY_A)
		mlx->cam->offsetx -= 25;
	else if (key == KEY_D)
		mlx->cam->offsetx += 25;
	else if (key == KEY_W)
		mlx->cam->offsety -= 25;
	else if (key == KEY_S)
		mlx->cam->offsety += 25;
	render(mlx);
}

/*
 * Key codes for Arrow Keys to Change Primary and Secondary colors in that order
 */
void	change_color(int key, t_mlx *mlx)
{
	int		i;
	int		color1;
	int		color2;

	color1 = mlx->map->color1;
	color2 = mlx->map->color2;
	i = mlx->map->iter;
	// Change Secondary Color
	if (key == KEY_LEFT)
	{
		if (i == 0)
			i = 63;
		color2 = mlx->map->colors[--i];
	}
	else if (key == KEY_RIGHT)
	{
		if (i == 63)
			i = 0;
		color2 = mlx->map->colors[++i];
	}
	// Change Primary Color
	else if (key == KEY_UP)
	{
		if (i == 63)
			i = 0;
		color1 = mlx->map->colors[++i];
	}
	else if (key == KEY_DOWN)
	{
		if (i == 0)
			i = 63;
		color1 = mlx->map->colors[--i];
	}
	mlx->map->iter = i;
	mlx->map->color2 = color2;
	mlx->map->color1 = color1;
	fill_colors(mlx->map, color1, color2);
	render(mlx);
}
