/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patrisor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 02:53:33 by patrisor          #+#    #+#             */
/*   Updated: 2019/05/29 00:00:00 by patrisor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define MENU_WIDTH 250
# define ERROR "error: "
# define USAGE "usage: ./fdf [map]"
# include "keycode_mac.h"
# include "colors.h"
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <limits.h>
# include <fcntl.h>
# include <stdlib.h>
// TODO: Store in libft
# define FT_MIN(A, B) (((A) < (B)) ? (A) : (B))

// TODO: DELETE
#include <stdio.h>

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
	int				color;
}					t_vector;

typedef struct		s_map
{
	int				width;
	int				height;
	int				depth_min;
	int				depth_max;
	t_vector		**vectors;
	// New
	int				*colors;
	int				color1;
	int				color2;
	int				iter;
}					t_map;

typedef struct		s_image
{
	void			*image;
	char			*ptr;
	int				bpp;
	int				stride;
	int				endian;
}					t_image;

typedef struct		s_cam
{
	double			offsetx;
	double			offsety;
	double			x;
	double			y;
	int				scale;
	double			**matrix;
}					t_cam;

typedef struct		s_mouse
{
	char			is_down;
	int				x;
	int				y;
	int				lastx;
	int				lasty;
}					t_mouse;

typedef struct		s_mlx
{
	void			*mlx;
	void			*window;
	t_image			*image;
	t_map			*map;
	t_cam			*cam;
	t_mouse			*mouse;
	// double			**zbuf;
}					t_mlx;

typedef struct		s_line
{
	t_vector		start;
	t_vector		stop;
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				err2;
}					t_line;

int					read_file(int fd, t_map **map);
t_map				*get_map(int width, int height);
t_vector			*get_vector(int x, int y, char *str);
void				fill_colors(t_map *map, int color1, int color2);
int					clerp(int c1, int c2, double p);
double				ft_ilerp(double val, double first, double second);
int					ft_lerpi(int first, int second, double p);
t_mlx				*init(char *title, t_map *map);
t_image				*del_image(t_mlx *mlx, t_image *img);
t_image				*new_image(t_mlx *mlx);
void				render(t_mlx *mlx);
void				clear_image(t_image *image);
t_vector			project_vector(t_vector v, t_mlx *mlx);
t_vector			vector_at(t_map *map, int x, int y);
t_vector			rotate(t_vector p, t_cam *r);
void				line(t_mlx *mlx, t_vector p1, t_vector p2);
int					lineclip(t_vector *p1, t_vector *p2);
int					region(int x, int y);
void				clip_xy(t_vector *v, t_vector *p1, t_vector *p2, int rout);
int					line_process_point(t_mlx *mlx, t_line *l, t_vector *p1, t_vector *p2);
void				image_set_pixel(t_image *image, int x, int y, int color);
int					hook_keydown(int key, t_mlx *mlx);
int					hook_mousedown(int button, int x, int y, t_mlx *mlx);
int					hook_mouseup(int button, int x, int y, t_mlx *mlx);
int					hook_mousemove(int x, int y, t_mlx *mlx);
// NEW
void				print_menu(t_mlx *lib);
void				setup_controls(t_mlx *mlx);
void				move(int key, t_mlx *mlx);
void				change_color(int key, t_mlx *mlx);

#endif
