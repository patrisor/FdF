/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 06:05:38 by patrisor          #+#    #+#             */
/*   Updated: 2019/05/20 13:42:07 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * LOGIC FOR ROTATION DURING RENDER. You take in the old vector values and you 
 * run trigonometric functions on the camera angle (manipulate t_cam, from 0.5
 * to 90.0, etc...)
 */
t_vector	rotate(t_vector p, t_cam *r)
{
	t_vector	v;

	// Change vector's x-position by rotating by x-axis (change two vectors, 
	// then add them together to get new vector position); Every vector changes
	// Without this, you just get a vertical line outputted
	v.x = cos(r->y) * p.x + sin(r->y) * p.z;
	// Change vector's z-position by rotating by z-axis; everything collapses or 
	// expands out from x axis reference point; this happens if sin is positive
	// This one causes the top hinges to not be fixed while moving
	// which distorts the shape drastically
	v.z = -sin(r->y) * p.x + cos(r->y) * p.z;
	// Change vector's y-position by rotating by z-axis
	// Without this, you just get a horizontal line outputted
	v.y = cos(r->x) * p.y - sin(r->x) * v.z;
	// If both Z's are out,the themap shrinks (squishes)
	// v.z changes based on y's vector
	v.z = sin(r->x) * p.y + cos(r->x) * v.z;
	// assign old color to new one
	v.color = p.color;
	return (v);
}
