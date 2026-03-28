/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 01:07:01 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/04/07 01:07:01 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

t_point	rotate_z(t_point *pt, double angle)
{
	t_point	res;

	res.x = pt->x * cos(angle) - pt->y * sin(angle);
	res.y = pt->x * sin(angle) + pt->y * cos(angle);
	res.z = pt->z;
	res.color = pt->color;
	return (res);
}

t_point	rotate_y(t_point *pt, double angle)
{
	t_point	res;

	res.x = pt->x * cos(angle) + pt->z * sin(angle);
	res.y = pt->y;
	res.z = pt->z * cos(angle) - pt->x * sin(angle);
	res.color = pt->color;
	return (res);
}

t_point	rotate_x(t_point *pt, double angle)
{
	t_point	res;

	res.x = pt->x;
	res.y = pt->y * cos(angle) - pt->z * sin(angle);
	res.z = pt->y * sin(angle) + pt->z * cos(angle);
	res.color = pt->color;
	return (res);
}

void	rotate_point(t_point *point, t_fdf *data)
{
	int	center_x;
	int	center_y;
	int	center_z;

	center_x = data->shift_x + ((data->cols - 1) * data->zoom) / 2;
	center_y = data->shift_y + ((data->rows - 1) * data->zoom) / 2;
	center_z = ((data->z_max + data->z_min) * data->zoom) / 2;
	point->x -= center_x;
	point->y -= center_y;
	point->z -= center_z;
	if (data->alpha != 0.0)
		*point = rotate_x(point, data->alpha);
	if (data->theta != 0.0)
		*point = rotate_y(point, data->theta);
	if (data->gamma != 0.0)
		*point = rotate_z(point, data->gamma);
	point->x += center_x;
	point->y += center_y;
	point->z += center_z;
}
