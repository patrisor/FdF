/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 21:47:03 by patrisor          #+#    #+#             */
/*   Updated: 2019/05/29 00:10:15 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * Handles hook events
 */
void	setup_controls(t_mlx *mlx)
{
	// Key-pressed user event
	mlx_key_hook(mlx->window, hook_keydown, mlx);
	// Mouse-pressed user event
	mlx_hook(mlx->window, 4, 0, hook_mousedown, mlx);
	// Mouse-up user event
	mlx_hook(mlx->window, 5, 0, hook_mouseup, mlx);
	// Mouse movement user event
	mlx_hook(mlx->window, 6, 0, hook_mousemove, mlx);
}

/*
 * Mlx loop hook which defines functions within key code presses
 */
int		hook_keydown(int key, t_mlx *mlx)
{
	// Casts mlx as void
	(void)mlx;
	// Key code for ESC
	if (key == KEY_ESCAPE)
		exit(EXIT_SUCCESS);
	// Key code for W, A, S, D
	else if (key == KEY_W || key == KEY_A || key == KEY_S ||
			key == KEY_D)
		move(key, mlx);
	// TODO: key code for color change
	else if (key == KEY_LEFT || key == KEY_RIGHT || 
			key == KEY_UP || key == KEY_DOWN)
		change_color(key, mlx);
	return (0);
}

/* 
 * Mouse-pressed user event
 */
int		hook_mousedown(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	if (y < 0)
		return (0);
	// Sets the mouse down parameter to one
	mlx->mouse->is_down |= 1 << button;
	return (0);
}

/*
 * Mouse-up user event
 */
int		hook_mouseup(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	mlx->mouse->is_down &= ~(1 << button);
	return (0);
}

/*
 * Mouse movement user event
 */
int		hook_mousemove(int x, int y, t_mlx *mlx)
{
	// Store current x and y values into last x and y values
	mlx->mouse->lastx = mlx->mouse->x;
	mlx->mouse->lasty = mlx->mouse->y;
	// Store parameters into current x and y values
	mlx->mouse->x = x;
	mlx->mouse->y = y;
	// Shifts the camera view if mouse is held down 
	if (mlx->mouse->is_down & (1 << 1))
	{
		// Shifts the camera view
		mlx->cam->x += (mlx->mouse->lasty - y) / 200.0f;
		mlx->cam->y -= (mlx->mouse->lastx - x) / 200.0f;
	}
	// If the right mouse button is clicked
	else if (mlx->mouse->is_down & (1 << 2))
	{
		// Scale the image
		mlx->cam->scale += (mlx->mouse->lasty - y) / 10.0f + 0.5f;
		if (mlx->cam->scale < 1)
			mlx->cam->scale = 1;
	}
	// If the mouse is down, continue rendering
	if (mlx->mouse->is_down)
		render(mlx);
	return (0);
}
