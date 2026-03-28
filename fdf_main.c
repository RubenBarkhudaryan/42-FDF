/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:12:38 by rbarkhud          #+#    #+#             */
/*   Updated: 2026/03/28 17:25:04 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

static void	init_data(t_fdf *dt, char *file_path)
{
	dt->mlx_ptr = mlx_init();
	dt->win_ptr = mlx_new_window(dt->mlx_ptr, WIDTH, HEIGHT, file_path);
	dt->img = mlx_new_image(dt->mlx_ptr, WIDTH, HEIGHT);
	dt->img_dt = mlx_get_data_addr(dt->img, &dt->bpp, &dt->sz_ln, &dt->endian);
	dt->zoom = 10;
	dt->shift_x = WIDTH / 2;
	dt->shift_y = HEIGHT / 4;
	dt->alpha = 0;
	dt->theta = 0;
	dt->gamma = 0;
	dt->rot_vel_x = 0;
	dt->rot_vel_y = 0;
	dt->rot_vel_z = 0;
	dt->auto_rotate = 0;
	dt->draw_isometric = 1;
	dt->render = 1;
	dt->low_color = 0x0000FF;
	dt->high_color = 0xFF0000;
	dt->seed = 0.5;
}

static int	end_session(t_fdf *data)
{
	if (!data)
		return (0);
	if (data->img)
		mlx_destroy_image(data->mlx_ptr, data->img);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_matrix(&(data->matrix), data->rows);
	free(data);
	return (0);
}

static int	close_window(t_fdf *data)
{
	end_session(data);
	exit(EXIT_SUCCESS);
	return (0);
}

static int	deal_key(int key, t_fdf *dt)
{
	if (key == 65362 || key == 119)
		move(-10, -10, dt);
	else if (key == 65364 || key == 115)
		move(10, 10, dt);
	else if (key == 65361 || key == 97)
		move(-10, 10, dt);
	else if (key == 65363 || key == 100)
		move(10, -10, dt);
	else if (key == 65307)
		close_window(dt);
	else if (key == 61 || key == 45 || key == 65451 || key == 65453)
		zoom(key, dt);
	else if (key >= 49 && key <= 51)
		rotate_drawing(key, dt);
	else if (key == 116 || key == 102 || key == 114 || key == 105)
	{
		dt->draw_isometric = 0;
		change_projection(key, dt);
	}
	else if (key == 'c')
		update_colors(dt);
	else if (key == 'o')
		toggle_auto_rotate(dt);
	dt->render = 1;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_fdf	*data;

	if (argc == 2 && is_valid_file(argv[1]))
	{
		data = parse_map(argv[1]);
		if (!data)
		{
			throw_error(-1);
			return (EXIT_FAILURE);
		}
		init_data(data, argv[1]);
		draw(data);
		mlx_hook(data->win_ptr, 2, 1L << 0, deal_key, data);
		mlx_hook(data->win_ptr, 17, 1L << 0, close_window, data);
		mlx_loop_hook(data->mlx_ptr, draw, data);
		mlx_loop(data->mlx_ptr);
	}
	else
		throw_error(2);
	return (0);
}
