/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 04:06:32 by patrisor          #+#    #+#             */
/*   Updated: 2019/05/20 14:14:18 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Linear Interpolation (Returns Percentage between two points)
 * Pass in the current state of the vector (1st param: Z-coord, 2nd: depth min, 
 * 3rd: depth max) to Shade? 
 * if 0 is returned, the color stays white, if 1 is returned, the color stays red
 * if anything higher is returned, the color becomes more dark
 */
double		ft_ilerp(double val, double first, double second)
{
	if (val == first)
		return (0.0);
	if (val == second)
		return (1.0);
	return ((val - first) / (second - first));
}

/*
 * if the first color is red, the first paramter will be 255
 * if the second color is white, the second parameter will be 255
 * the third parameter states what color it should be based on z-coord
 */
int		ft_lerpi(int first, int second, double p)
{
	if (first == second)
		return (first);
	return ((int)((double)first + (second - first) * p));
}
