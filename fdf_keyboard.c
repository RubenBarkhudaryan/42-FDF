/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_keyboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 02:24:17 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/04/07 02:24:17 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void	rotate_drawing(int key, t_fdf *data)
{
	if (key == 49)
		data->gamma += 0.04;
	else if (key == 50)
		data->theta += 0.04;
	else if (key == 51)
		data->alpha += 0.04;
}

void	zoom(int key, t_fdf *data)
{
	if ((key == 61 || key == 65451) && data->zoom < 70)
	{
		if (data->zoom + 1 == 0)
			data->zoom = 1;
		else
			data->zoom += 1;
	}
	else if ((key == 45 || key == 65453) && data->zoom > -70)
	{
		if (data->zoom - 1 == 0)
			data->zoom = -1;
		else
			data->zoom -= 1;
	}
}

void	change_projection(int key, t_fdf *dt)
{
	if (key == 116)
	{
		dt->alpha = 0;
		dt->theta = 0;
		dt->gamma = 0;
	}
	else if (key == 102)
	{
		dt->alpha = 89.55;
		dt->theta = 122.5;
		dt->gamma = 0;
	}
	else if (key == 114)
	{
		dt->alpha = 0;
		dt->theta = -89.54;
		dt->gamma = 89.55;
	}
	else if (key == 105)
	{
		dt->draw_isometric = 1;
		dt->alpha = 0;
		dt->theta = 0;
		dt->gamma = 0;
	}
}

void	update_colors(t_fdf *data)
{
	data->low_color = pseudo_random_color(data->seed);
	data->seed += 0.5;
	data->high_color = pseudo_random_color(data->seed);
}

void	toggle_auto_rotate(t_fdf *data)
{
	data->auto_rotate = !data->auto_rotate;
}
