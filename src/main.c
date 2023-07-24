/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:00:14 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/24 23:44:20 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	close_window(mlx_key_data_t keydata, t_data *d)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		clean_up(d);
		mlx_terminate(d->mlx);
		exit(0);
	}

}

// void	resize_window(int32_t width, int32_t height, t_data *d)
// {
// 	printf("h: %d, w: %d\n", height, width);
// 	d->img = mlx_new_image(d->mlx, height, width);
// 	if (mlx_image_to_window(d->mlx, d->img, 0, 0) < 0)
// 	{
// 		clean_up(d);
// 		error((t_err){mlx_strerror(mlx_errno), NULL, 0, EXIT, 1});
// 	}
// }

int	main(int argc, char *argv[])
{
	t_data	d;

	ft_memset(&d, 0, sizeof(t_data));
	parse_input(&d, argc, argv);
	populate_window_properties(&d);
	set_up_scn_el_ptrs(&d);
	set_up_ctw_mx(&d);
	d.mlx = mlx_init(CANVAS_W, CANVAS_H, "MiniRT", true);
	if (!d.mlx)
	{
		clean_up(&d);
		error((t_err){mlx_strerror(mlx_errno), NULL, 0, EXIT, 1});
	}
	d.img = mlx_new_image(d.mlx, CANVAS_W, CANVAS_H);
	render_scene(&d, CANVAS_W, CANVAS_H);
	if (!d.img || (mlx_image_to_window(d.mlx, d.img, 0, 0) < 0))
	{
		clean_up(&d);
		error((t_err){mlx_strerror(mlx_errno), NULL, 0, EXIT, 1});
	}
	// mlx_resize_hook(d.mlx, (void *)resize_window, &d);
	mlx_key_hook(d.mlx, (void *)close_window, &d);
	mlx_loop(d.mlx);
	clean_up(&d);
	mlx_terminate(d.mlx);
	system("leaks minirt");
	return (EXIT_SUCCESS);
}
