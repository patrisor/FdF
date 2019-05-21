/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:54:48 by patrisor          #+#    #+#             */
/*   Updated: 2019/05/20 22:43:36 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		die(char *reason)
{
	ft_putendl(reason);
	return (1);
}

// TODO: Delete Test function
void	test_values(t_map *map)
{
	int			x;
	int			y;
	t_vector	*v;

	printf("Map Test:\nWidth: %d, Height: %d, Depth_min: %d, "
			"Depth_max: %d\nVector Test:\n", map->width, map->height, map->depth_min, map->depth_max);
	y = 0;
	while(y < map->height)
	{
		x = 0;
		while(x < map->width)
		{
			v = map->vectors[y * map->width + x];
			printf("X: %f, Y: %f, Z: %f, color: %d\n", v->x, v->y, v->z, v->color);
			x++;
		}
		y++;
	}
}

int		main(int argc, char **argv)
{
	// Create a map structure in memory, corresponding to the features 
	// on the GUI, it's depth, height, depth_min and _max, and vectors.
	t_map	*map;
	// Reserve a spot in memory for the graphics state settings, like the image, 
	// () map, camera (thing that reserves light from pixels), and mouse events
	t_mlx	*mlx;
	int		fd;

	if (argc != 2)
		return die(USAGE);
	// Open a file called argv[1] and pass the file descriptor to a variable 
	// called 'fd' with a RD_ONLY flag.
	fd = open(argv[1], O_RDONLY);
	// Fills the map eement in memory with values based on the state of the 
	// numbers passed within the file descriptor
	// Error check: if the fd is less than zero OR if the read_file returns 0, 
	// then the file is invalid
	if (fd < 0 || !read_file(fd, &map))
		return (die(ft_strjoin(ERROR, "invalid file")));
	// init function takes a parameter of what will show up on top of the window
	// initializes our mlx environment by filling structs in memory associated with it
	// with different values. We call functions from the library to make it all work
	if ((mlx = init(ft_strjoin("FdF - ", argv[1]))) == NULL)
		return (die(ft_strjoin(ERROR, "mlx couldn't init")));
	// Passes the map into map
	mlx->map = map;
	// Function will continuously update our image
	render(mlx);
	// Key-pressed user event
	mlx_key_hook(mlx->window, hook_keydown, mlx);
	// Mouse-pressed user event
	mlx_hook(mlx->window, 4, 0, hook_mousedown, mlx);
	// Mouse-up user event
	mlx_hook(mlx->window, 5, 0, hook_mouseup, mlx);
	// Mouse movement user event
	mlx_hook(mlx->window, 6, 0, hook_mousemove, mlx);
	// It is an infinite loop that waits for an event, and then calls a 
	// user-defined function associated with this event.
	mlx_loop(mlx->mlx);
	return (0);
}
