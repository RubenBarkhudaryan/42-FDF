/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 00:46:11 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/04/03 00:46:11 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H
# define WIDTH 1080
# define HEIGHT 1080

# include "./includes/gnl/get_next_line.h"
# include "./includes/libft/libft.h"
# include "./mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct fdf
{
	int		rows;
	int		cols;

	int		z_min;
	int		z_max;

	int		zoom;
	int		shift_x;
	int		shift_y;
	int		**matrix;

	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;

	char	*img_dt;
	int		bpp;
	int		sz_ln;
	int		endian;

	float	alpha;
	float	theta;
	float	gamma;

	int		draw_isometric;
	int		render;

	int		low_color;
	int		high_color;
	float	seed;
}	t_fdf;

typedef struct line
{
	char	*str;
	char	**split;
}	t_line;

typedef struct point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct trgb
{
	int	t;
	int	r;
	int	g;
	int	b;
}	t_trgb;

typedef struct colors
{
	int	start_color;
	int	end_color;
}	t_clr;

/* file manipulating functions */
int		file_length(char *file_path);
int		is_valid_file(char *str);
t_fdf	*parse_map(char *file_path);

/* parser helper functions */
void	free_matrix(int ***matrix, int target_ind);
void	free_split(char ***split);
int		row_len(char **split);
void	throw_error(int error_status);

/*keyboard actions*/
void	rotate_drawing(int key, t_fdf *data);
void	zoom(int key, t_fdf *data);
void	change_projection(int key, t_fdf *dt);
void	update_colors(t_fdf *data);

/* drawing functions */
void	draw_panel_background(t_fdf *dt);
void	draw_controls_panel(t_fdf *dt);
void	move(int x, int y, t_fdf *data);
void	draw_line(t_point *pt1, t_point *pt2, t_fdf *data);
int		draw(t_fdf *data);
void	slope_less_than_one(t_point *delta, t_point *st, t_fdf *dt, t_clr c);
void	slope_bigger_than_one(t_point *delta, \
	t_point *st, t_fdf *dt, t_clr c);

/*gradient from color*/
int		get_color(int z, int z_min, int z_max, t_fdf *dt);
int		interpolate_color(int s_color, int e_color, float fraction);
double	pseudo_rand(float seed);
int		pseudo_random_color(float seed);

/*rotate drawing*/
t_point	rotate_z(t_point *pt, double angle);
t_point	rotate_y(t_point *pt, double angle);
t_point	rotate_x(t_point *pt, double angle);
void	rotate_point(t_point *point, t_fdf *data);

#endif