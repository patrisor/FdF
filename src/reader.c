/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 07:38:27 by patrisor          #+#    #+#             */
/*   Updated: 2019/05/14 01:38:28 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Free all associated addresses
 */
static int		garbage_collect(t_list **lst, t_map **map)
{
	// Address to individual node in linked list
	t_list		*next;

	// Iterate through list
	while(*lst)
	{
		// set next list to the variable next
		next = (*lst)->next;
		// Delete / Free the memory address of content pointed by list
		ft_memdel(&(*lst)->content);
		// Frees the address of the list passed
		ft_memdel((void **)lst);
		// Iterate to next list
		*lst = next;
	}
	// if the map contents exist, then free them too
	if(map && *map)
	{
		// Frees map
		ft_memdel((void **)&(*map)->vectors);
		// Frees vectors
		ft_memdel((void **)map);
	}
	return (0);
}

/**
 * Reads lines individually from file and stores them into a linked list, then
 * the string is freed
 */
static int		get_lines(int fd, t_list **lst)
{
	t_list		*temp;
	int			expected;
	char		*line;
	int			bytes;

	expected = -1;
	// man get_next_line: function which reads a line from stream, delimited by 
	// the '\n' character into the variable line.
	// Returns number of characters (bytes) written OR -1 if error has occured
	while((bytes = get_next_line(fd, &line)))
	{
		if(expected == -1)
			expected = ft_countwords(line, ' '); // Returns # of file row #'s	
		// Create a new list based on the size of the row and the content is the 
		// row itself
		temp = ft_lstnew(line, ft_strlen(line) + 1);
		// Error check: if list is empty, garbage collect; frees all memory
		if((temp) == NULL)
			return (garbage_collect(lst, NULL));
		// Append temp to lst passed as argument
		ft_lstadd(lst, temp);
		// TODO: I feel like this is a pointless error check, since the last time it 
		// was checked, the state never changes.
		if(expected != (int)ft_countwords(line, ' '))
			return (garbage_collect(lst, NULL));
		// Frees the line once it has been used
		ft_strdel(&line);
	}
	// Simple error checking: if expected has not changed OR the bytes have not 
	// been read
	if(expected == -1 || bytes == -1)
		return (garbage_collect(lst, NULL));
	// TODO: IMPORTANT: Reverses content of the list to flip to computer coordinate 
	// system
	ft_lstrev(lst);
	return (1);
}

/*
 * Iterates the entirety of the map to find and assign the minimum and maximum values
 */
void	find_depth(t_map *map)
{
	int			min;
	int			max;
	t_vector	v;
	t_vector	cur;

	// TODO: figure out why pbondoer's implementation has these values flipped. Bug in his 
	// code?
	// Value of INT_MAX is +2147483647.
	max = INT_MAX;
	// Value of INT_MIN is -2147483647.
	min = INT_MIN;
	v.y = 0;
	// Traverses down the heaight of the map
	while (v.y < map->height)
	{
		v.x = 0;
		// Traverses through each element in row
		while (v.x < map->width)
		{
			// Assigns cur to every spot in the map of vectors to find min and max values
			cur = *map->vectors[(int)v.y * map->width + (int)v.x];
			// condition to find max values
			if (cur.z < max)
				max = cur.z;
			// condition to find min values
			if (cur.z > min)
				min = cur.z;
			v.x++;
		}
		v.y++;
	}
	// assigns max value
	map->depth_min = max;
	// assigns min value
	map->depth_max = min;
}

/* TODO: Delete
#include <stdio.h>
void	ft_putvector(t_vector	**vectors)
{
	t_vector	*vector;
	int			i;

	i = 0;
	while(vectors[i])
	{
		vector = vectors[i];
		printf("x: %d, y: %d, z: %d\n", (int)vector->x, (int)vector->y, (int)vector->z);
		i++;
	}
}
*/

// TODO: Delete Test Function
void	ft_putlst(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while(tmp != NULL)
	{
		ft_putstr(ft_strjoin((char *)tmp->content, "\n"));
		tmp = tmp->next;
	}
}

/*
 * Fills the map struct with the rest of the values associated with itself, such as 
 * the vector values, colors, and depth_min and max.
 */
static int	populate_map(t_map **map, t_list *list)
{
	// instantiates map
	t_list	*lst;
	// instantiates a character map (multiple rows and columns)
	char	**split;
	// instantiates x position
	int		x;
	// instantiates y position
	int		y;

	lst = list;
	y = 0;
	// Traverses down the height of the map
	while(y < (*map)->height)
	{
		// will always start from the left position
		x = 0;
		// Error check; will attempt to split the contents of the list by their 
		// individual values
		if ((split = ft_strsplit(lst->content, ' ')) == NULL)
			return (garbage_collect(&list, map));
		// Iterates through each individual value of the lst-content
		while (x < (*map)->width)
		{
			// Individually fills the content of the vector data by the information 
			// gathered from the file
			// IMPORTANT: Maps it at the memory area at that particular point which it 
			// read from the file (vectors[5 * 10 + 7] = vectors[57])
			(*map)->vectors[y * (*map)->width + x] = get_vector(x, y, split[x]);
			x++;
		}
		// Pass the address of every point in that map in which you split and delete the content
		// along with the addresses associated with each point
		ft_splitdel(&split);
		// Goes to the next node in the list
		lst = lst->next;
		y++;
	}
	// Iterates the entirety of the map to find and assign the minimum and maximum values
	find_depth(*map);
	// Assigns cur to every spot in the map of vectors so that it can call it's own 
	// address to color 
	fill_colors(*map);
	// Deletes the contents of list and frees it's associated addressed
	garbage_collect(&list, NULL);
	return (1);
}

/**
 * Main read function which reads contents of file and populates our node elements 
 * based on the contents 
 */
int		read_file(int fd, t_map **map)
{
	// Create a linked list
	t_list	*lst;

	// Set the lst head address to NULL
	lst = NULL;
	// Call a get_lines function to get the full list of lines in a file
	// if it returns null, the return 0 for an error (invalid file in main)
	if(!(get_lines(fd, &lst)))
		return (0);
	// count the rows and columns of the lst and pass it into  get_map()
	*map = get_map(ft_countwords(lst->content, ' '), ft_lstcount(lst));
	// Error checking to see if get_map worked
	if(*map == NULL)
		return(garbage_collect(&lst, map));
	// Returns 1 once the map becomes populated, or 0 if any of the functions return NULL
	return (populate_map(map, lst));
}
