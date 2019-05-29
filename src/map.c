/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 17:01:09 by patrisor          #+#    #+#             */
/*   Updated: 2019/05/28 18:59:21 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
 * Fills every single vector with a color
 * Added a gradient effect
 */
void	fill_colors(t_map *map)
{
	t_vector	v;
	t_vector	*cur;

	v.y = 0;
	// Traverses down the heaight of the map
	while(v.y < map->height)
	{
		v.x = 0;
		// Traverses through each element in row
		while(v.x < map->width)
		{
			// Assigns cur to every spot in the map of vectors so that it can 
			// call it's own address to color
			cur = map->vectors[(int)v.y * map->width + (int)v.x];
			// Gives the Gradient effect from white (0xFFFFFF) to red (0xFF0000) ->
			// for every vector, the color will shift based on the vector state.
			cur->color = clerp(0xFF0000, 0xFFFFFF, ft_ilerp(cur->z, 
						map->depth_min, map->depth_max));
			v.x++;
		}
		v.y++;
	}
}

/*
 * Function manipulates state of vector to vector prime.
 */
t_vector	project_vector(t_vector v, t_mlx *mlx)
{
	// Offsets initial state of vector by -4; v.x = v.x - ()
	v.x -= (double)(mlx->map->width - 1) / 2.0f;
	// Offsets initial state of vector by -4
	v.y -= (double)(mlx->map->height - 1) / 2.0f;
	// Offsets initial state of vector by -4
	v.z -= (double)(mlx->map->depth_min + mlx->map->depth_max) / 2.0f;
	// LOGIC FOR ROTATION DURING RENDER
	v = rotate(v, mlx->cam);
	// Independently scales x coord
	v.x *= mlx->cam->scale;
	// Independently scales y coord
	v.y *= mlx->cam->scale;
	// TODO: 
	// Independently offsets x coord; OLD: mlx->cam->offsetx;
	v.x += mlx->cam->offsetx;
	// Independently offsets y coord; OLD: mlx->cam->offsety;
	v.y += mlx->cam->offsety;
	return (v);
}

/*
 * Returns vector object found at that particular coordinate pointed by the map.
 */
t_vector	vector_at(t_map *map, int x, int y)
{
	return (*map->vectors[y * map->width + x]);
}

/*
 * Create a new vector with the given parameters
 */
t_vector	*get_vector(int x, int y, char *str)
{
	t_vector	*v;

	// allocate memory for new vector
	v = ft_memalloc(sizeof(t_vector));
	// Error check
	if (v == NULL)
		return (NULL);
	// X-position
	v->x = (double)x;
	// Y-position
	v->y = (double)y;
	// Z-position, where the vector protrudes out
	v->z = (double)ft_atoi(str);
	// Color (Hex): White
	v->color = 0xFFFFFF;
	return (v);
}

/*
 * Function which creates a new map object and fills it with values. Width will 
 * be the length of row in list content. Height is how many elements are in list.
 */
t_map	*get_map(int width, int height)
{
	// instantiate a new map object in memory
	t_map	*map;

	// allocate memory to fit this map inside heap
	map = ft_memalloc(sizeof(t_map));
	// Error check
	if (map == NULL)
		return (NULL);
	// Fill values of map with the ones passed as parameter
	// Map width
	map->width = width;
	// Map height
	map->height = height;
	// Map depth minimum
	map->depth_min = 0;
	// Map depth maximum
	map->depth_max = 0;
	// Vectors of map
	map->vectors = ft_memalloc(sizeof(t_vector *) * width * height);
	// Error check vectors
	if (map->vectors == NULL)
	{
		// Delete the address of map
		ft_memdel((void **)&map);
		return (NULL);
	}
	return (map);
}
