/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:00:14 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/02 22:38:59 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <minirt.h>
#include <stdlib.h>

void	fn(void)
{
	system("leaks minirt");
}

int	main(int argc, char *argv[])
{
	t_data	d;

	ft_memset(&d, 0, sizeof(t_data));
	atexit(fn);
	parse_input(&d, argc, argv);
	set_up_scn_el_ptrs(&d);
	set_up_ctw_mx(&d);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
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
	mlx_key_hook(d.mlx, (void *)close_window, &d);
	mlx_loop(d.mlx);
	mlx_terminate(d.mlx);
	clean_up(&d);
	return (EXIT_SUCCESS);
}
