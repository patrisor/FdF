/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lineclip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 17:43:25 by patrisor          #+#    #+#             */
/*   Updated: 2019/05/20 19:37:27 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * Manipulates & returns a number based on where the x and y axis are located
 */
int		region(int x, int y)
{
	int		c;

	c = 0;
	// Condition which checks if the y passed is greater than the window height
	if (y >= WIN_HEIGHT)
		// c will be equal to 1
		c |= 1;
	// Condition which checks if the y passed is less than 0
	else if (y < 0)
		// c will be equal to 2
		c |= 2;
	// Condition which checks if the x passed is greater than the window width
	if (x >= WIN_WIDTH)
		// if y >= WIN_HEIGHT, then c = 5 (Bottom-Left)
		// if y < 0, then c = 6 (Bottom-Right)
		c |= 4;
	else if (x < 0)
		// if y >= WIN_HEIGHT, then c = 9 (Top-Left)
		// if y < 0, then c = 10 (Top-Right)
		c |= 8;
	return (c);
}

/*
 * Clips the old x and y to create a new value for the vector, based on the region
 */
void	clip_xy(t_vector *v, t_vector *p1, t_vector *p2, int rout)
{
	// Checks if the region taken as parameter is equal to 1
	if (rout & 1)
	{
		// Formula to clip the old x and y
		v->x = p1->x + (p2->x - p1->x) * (WIN_HEIGHT - p1->y) / (p2->y - p1->y);
		v->y = WIN_HEIGHT - 1;
	}
	// Checks if the region taken as parameter is equal to 2
	else if (rout & 2)
	{
		// Formula to clip the old x and y
		v->x = p1->x + (p2->x - p1->x) * -p1->y / (p2->y - p1->y);
		v->y = 0;
	}
	// Checks if the region taken as parameter is equal to 4
	else if (rout & 4)
	{
		// Formula to clip the old x and y
		v->x = WIN_WIDTH - 1;
		v->y = p1->y + (p2->y - p1->y) * (WIN_WIDTH - p1->x) / (p2->x - p1->x);
	}
	else
	{
		// Formula to clip the old x and y
		v->x = 0;
		v->y = p1->y + (p2->y - p1->y) * -p1->x / (p2->x - p1->x);
	}
}

/*
 * Method to selectively enable or disable rendering operations within a defined 
 * region of interest; if the line drawn will not be seen like outside of the screen
 */
int		lineclip(t_vector *p1, t_vector *p2)
{
	t_vector	v;
	int			r1;
	int			r2;
	int			rout;

	// Manipulates & returns a number based on where the x and y axis are located
	r1 = region(p1->x, p1->y);
	// Manipulates & returns a number based on where the x and y axis are located
	r2 = region(p2->x, p2->y);
	// This loop will run if any of the bitwise operations against the regions equal 
	// zero.
	while (!(!(r1 | r2) || (r1 & r2)))
	{
		// If r1 is equal to 0, rout becomes r2, else rout becomes r1
		rout = r1 ? r1 : r2;
		// Clips the old x and y to create a new value for the vector, based on the 
		// region
		clip_xy(&v, p1, p2, rout);
		// Checks regions
		if (rout == r1)
		{
			// Manipulates coordinate based on the clipped values
			p1->x = v.x;
			p1->y = v.y;
			// Checks for region with new values
			r1 = region(p1->x, p1->y);
		}
		else
		{
			// Manipulates coordinate based on the clipped values
			p2->x = v.x;
			p2->y = v.y;
			// Checks for region with new values
			r2 = region(p2->x, p2->y);
		}
	}
	// Returns 1 if the bitwise operation against the regions become zero. Or you 
	// are in the middle of the screen
	return (!(r1 | r2));
}
