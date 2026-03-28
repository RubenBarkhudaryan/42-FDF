/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 20:04:54 by rbarkhud          #+#    #+#             */
/*   Updated: 2026/03/28 17:03:59 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

static void	isometric(int *x, int *y, int z)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = *x;
	tmp_y = *y;
	*x = (tmp_x - tmp_y) * cos(0.523599);
	*y = (tmp_x + tmp_y) * sin(0.523599) - z;
}

static t_point	init_temp_ptr(t_point *src, t_fdf *dt)
{
	t_point	tmp;

	tmp = *src;
	tmp.z = dt->matrix[tmp.y][tmp.x] * dt->zoom;
	tmp.x *= dt->zoom;
	tmp.y *= dt->zoom;
	tmp.x += dt->shift_x;
	tmp.y += dt->shift_y;
	rotate_point(&tmp, dt);
	if (dt->draw_isometric)
		isometric(&tmp.x, &tmp.y, tmp.z);
	tmp.color = get_color(dt->matrix[src->y][src->x], dt->z_min, dt->z_max, dt);
	return (tmp);
}

void	move(int x, int y, t_fdf *data)
{
	data->shift_x += x;
	data->shift_y += y;
}

void	draw_line(t_point *pt1, t_point *pt2, t_fdf *dt)
{
	t_point	t1;
	t_point	t2;
	t_point	delta;

	t1 = init_temp_ptr(pt1, dt);
	t2 = init_temp_ptr(pt2, dt);
	delta.y = t2.y - t1.y;
	delta.x = t2.x - t1.x;
	if (abs(delta.x) > abs(delta.y))
		slope_less_than_one(&delta, &t1, dt, ((t_clr){t1.color, t2.color}));
	else
		slope_bigger_than_one(&delta, &t1, dt, ((t_clr){t1.color, t2.color}));
}

int	draw(t_fdf *dt)
{
	t_point	pt1;

	if (dt->render == 0)
		return (0);
	mlx_destroy_image(dt->mlx_ptr, dt->img);
	dt->img = mlx_new_image(dt->mlx_ptr, WIDTH, HEIGHT);
	dt->img_dt = mlx_get_data_addr(dt->img, &dt->bpp, &dt->sz_ln, &dt->endian);
	pt1.y = 0;
	while (pt1.y < dt->rows)
	{
		pt1.x = 0;
		while (pt1.x < dt->cols)
		{
			if (pt1.x < dt->cols - 1)
				draw_line(&pt1, (&(t_point){pt1.x + 1, pt1.y, 0, 0}), dt);
			if (pt1.y < dt->rows - 1)
				draw_line(&pt1, (&(t_point){pt1.x, pt1.y + 1, 0, 0}), dt);
			pt1.x++;
		}
		pt1.y++;
	}
	draw_panel_background(dt);
	mlx_put_image_to_window(dt->mlx_ptr, dt->win_ptr, dt->img, 0, 0);
	draw_controls_panel(dt);
	return (dt->render = 0, 1);
}
