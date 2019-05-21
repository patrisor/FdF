/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 01:20:06 by patrisor          #+#    #+#             */
/*   Updated: 2019/05/20 20:41:53 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// The higher the Z, the closer to the second color it is going to be.

/*
 * If put into a loop, it will produce the Gradient effect from white (0xFFFFFF) 
 * to red (0xFF0000) -> for every vector color value, this happenes because the 
 * color will shift based on the vector state, it's z-coordinate value. */
int		clerp(int c1, int c2, double p)
{
	int		r;
	int		g;
	int		b;

	// If the two colors passed are the same, then return the first color 
	// passed
	if (c1 == c2)
		return (c1);
	// c1(RED) = 1111 1111 0000 0000 0000 0000 / 0xFF0000
	// c2(WHITE) = 1111 1111 1111 1111 1111 1111 / 0xFFFFFF
	// manipulates red value of final color; this will return 255
	r = ft_lerpi((c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, p);
	// manipulates green
	g = ft_lerpi((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, p);
	// manipulates blue
	b = ft_lerpi(c1 & 0xFF, c2 & 0xFF, p);
	// Further manipulates the RGB Values
	return (r << 16 | g << 8 | b);
}

/*
 * Function finds the percent between two vectors, and starts setting pixels 
 * in between those points
 */
int		line_process_point(t_mlx *mlx, t_line *l, t_vector *p1, t_vector *p2)
{
	double	percent;

	// Error checking
	if (p1->x < 0 || p1->x >= WIN_WIDTH || p1->y < 0 || p1->y >= WIN_HEIGHT 
			|| p2->x < 0 || p2->x >= WIN_WIDTH || p2->y < 0 || p2->y >= WIN_HEIGHT)
		return (1);
	// Find the percent between the two vectors
	percent = (l->dx > l->dy ? 
			ft_ilerp((int)p1->x, (int)l->start.x, (int)l->stop.x) 
			: ft_ilerp((int)p1->y, (int)l->start.y, (int)l->stop.y));
	// Sets the pixel at that particular point
	image_set_pixel(mlx->image, (int)p1->x, (int)p1->y, clerp(p1->color, 
				p2->color, percent));
	// Err is half the distance between two points
	l->err2 = l->err;
	// TODO: What is this?
	if (l->err2 > -l->dx)
	{
		l->err -= l->dy;
		p1->x += l->sx;
	}
	if (l->err2 < l->dy)
	{
		l->err += l->dx;
		p1->y += l->sy;
	}
	return (0);
}

/* TODO: Find a more efficient line algorithm
 * Draws line in between two vector points; Accounts for clipping.
 */
void	line(t_mlx *mlx, t_vector p1, t_vector p2)
{
	// Creates a line object
	t_line	line;

	// Converts every double to an int
	p1.x = (int)p1.x;
	p2.x = (int)p2.x;
	p1.y = (int)p1.y;
	p2.y = (int)p2.y;
	// Sets the first vector as the anchor point to the line
	line.start = p1;
	line.stop = p2;
	// TODO: Understand Clipping
	// Method to selectively enable or disable rendering operations within 
	// a defined region of interest. Increases performance by calculating less
	if (!lineclip(&p1, &p2))
		return ;
	// Fills d.x portion of line by subtracting two x's
	line.dx = abs((int)p2.x - (int)p1.x);
	// TODO: Understand what this is 
	line.sx = (int)p1.x < (int)p2.x ? 1 : -1;
	// Fills d.y portion of line by subtracting two y's
	line.dy = abs((int)p2.y - (int)p1.y);
	// TODO: Understand what this is
	line.sy = (int)p1.y < (int)p2.y ? 1 : -1;
	// TODO: Understand what this is
	line.err = (line.dx > line.dy ? line.dx : -line.dy) / 2;
	// Actually Draws the line
	while (((int)p1.x != (int)p2.x || (int)p1.y != (int)p2.y))
		// Function finds the percent between two vectors, and starts setting 
		// pixels in between those points
		if (line_process_point(mlx, &line, &p1, &p2))
			break ;
}

/*
 * This is stored within our loop which will continuously update our image
 * by drawing inside the image, then dumping it inside a specified window at
 * any time to display it on the screen.
 */
void	render(t_mlx *mlx)
{
	int			x;
	int			y;
	t_vector	v;
	t_map		*map;

	// Pass in adjusted map into created object
	map = mlx->map;
	// Clears content of the memory address without freeing the pointer
	clear_image(mlx->image);
	// Iterate through the columns of the map
	x = 0;
	while (x < map->width)
	{
		// Iterate through the rows of the map
		y = 0;
		while (y < map->height)
		{
			// Projects a vector at that particular coordinate by manipulating 
			// the state of the camera angle at all points
			v = project_vector(vector_at(map, x, y), mlx);
			// Condition which checks if the next point on x axis is still less
			// than the width of the map
			if (x + 1 < map->width)
				// Draws line in between two vector points; Accounts for clipping.
				line(mlx, v, project_vector(vector_at(map, x + 1, y), mlx));
			// Condition which checks if the next point on y axis is still less
			// than the heigth of the map
			if (y + 1 < map->height)
				// Draws line in between two vector points; Accounts for clipping.
				line(mlx, v, project_vector(vector_at(map, x, y + 1), mlx));
			y++;
		}
		x++;
	}
	// Displays the image onto the display: three identifiers are needed here, 
	// for the connection to the display, the window to use, and the image 
	// (respectively mlx_ptr, win_ptr, and img_ptr)
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
}
