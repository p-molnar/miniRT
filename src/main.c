/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:00:14 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/09 18:22:44 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <minirt.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_data	data;
	char	*titlebar;

	ft_memset(&data, 0, sizeof(t_data));
	parse_input(&data, argc, argv);
	set_up_scn_el_ptrs(&data);
	set_up_ctw_mx(&data);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	titlebar = strconcat(3, NAME, " - ", argv[1]);
	data.mlx = mlx_init(CANVAS_W, CANVAS_H, titlebar, true);
	free(titlebar);
	if (!data.mlx)
		mlx_err(&data);
	data.img = mlx_new_image(data.mlx, CANVAS_W, CANVAS_H);
	render_scene(&data, CANVAS_W, CANVAS_H);
	if (!data.img || (mlx_image_to_window(data.mlx, data.img, 0, 0) < 0))
		mlx_err(&data);
	mlx_key_hook(data.mlx, (void *)close_window, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	clean_up(&data);
	return (EXIT_SUCCESS);
}
