/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_panel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:04:16 by rbarkhud          #+#    #+#             */
/*   Updated: 2026/03/28 17:04:16 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void	draw_panel_background(t_fdf *dt)
{
	char	*dst;
	int		x;
	int		y;

	y = 16;
	while (y < 232)
	{
		x = 16;
		while (x < 360)
		{
			dst = dt->img_dt + (y * dt->sz_ln + x * (dt->bpp / 8));
			*(unsigned int *)dst = 0x101015;
			x++;
		}
		y++;
	}
}

void	draw_controls_panel(t_fdf *dt)
{
	mlx_string_put(dt->mlx_ptr, dt->win_ptr, 28, 34, 0xFFFFFF, "FDF Controls");
	mlx_string_put(dt->mlx_ptr, dt->win_ptr, 28, 62, 0xD0D0D0,
		"Move: Arrows or W A S D");
	mlx_string_put(dt->mlx_ptr, dt->win_ptr, 28, 84, 0xD0D0D0, "Zoom: + / -");
	mlx_string_put(dt->mlx_ptr, dt->win_ptr, 28, 106, 0xD0D0D0, "Rotate Z: 1");
	mlx_string_put(dt->mlx_ptr, dt->win_ptr, 28, 128, 0xD0D0D0, "Rotate Y: 2");
	mlx_string_put(dt->mlx_ptr, dt->win_ptr, 28, 150, 0xD0D0D0, "Rotate X: 3");
	mlx_string_put(dt->mlx_ptr, dt->win_ptr, 28, 150, 0xD0D0D0,
		"Auto Rotate: o");
	mlx_string_put(dt->mlx_ptr, dt->win_ptr, 28, 172, 0xD0D0D0,
		"Projection: T / F / R / I");
	mlx_string_put(dt->mlx_ptr, dt->win_ptr, 28, 194, 0xD0D0D0,
		"Random colors: C");
	mlx_string_put(dt->mlx_ptr, dt->win_ptr, 28, 216, 0xD0D0D0, "Exit: ESC");
}
