/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:00:14 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/21 13:26:10 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	set_up_scn_el_ptrs(t_data *d)
{
	d->scn_els[AMB_LIGHT] = get_scn_els(d->all_scn_el, F_AMB_LIGHT);
	d->scn_els[CAM] = get_scn_els(d->all_scn_el, F_CAM | F_TG_CAM);
	d->scn_els[POINT_LIGHT] = get_scn_els(d->all_scn_el, F_POINT_LIGHT);
	d->scn_els[DIR_LIGHT] = get_scn_els(d->all_scn_el, F_DIR_LIGHT);
	d->scn_els[SPHERE] = get_scn_els(d->all_scn_el, F_SPHERE);
	d->scn_els[PLANE] = get_scn_els(d->all_scn_el, F_PLANE);
	d->scn_els[CYLINDER] = get_scn_els(d->all_scn_el, F_CYLINDER);
	d->scn_els[CYLINDER_CAP] = get_scn_els(d->all_scn_el, F_CYLINDER_CAP);
	d->scn_els[ALL_LIGHTS] = get_scn_els(d->all_scn_el, G_LIGHTS);
	d->scn_els[ALL_OBJS] = get_scn_els(d->all_scn_el, G_OBJS);
}

int	main(int argc, char *argv[])
{
	t_data	d;

	ft_memset(&d, 0, sizeof(t_data));
	parse_input(&d, argc, argv);
	set_up_scn_el_ptrs(&d);
	set_up_ctw_mx(&d);
	d.mlx = mlx_init(CANVAS_W + 5, CANVAS_H + 5, "MiniRT", true);
	if (!d.mlx)
	{
		clean_up(&d);
		error((t_err){mlx_strerror(mlx_errno), NULL, 0, EXIT, 1});
	}
	d.img = mlx_new_image(d.mlx, CANVAS_W, CANVAS_H);
	if (!d.img || (mlx_image_to_window(d.mlx, d.img, 0, 0) < 0))
	{
		clean_up(&d);
		error((t_err){mlx_strerror(mlx_errno), NULL, 0, EXIT, 1});
	}
	render_scene(&d);
	clean_up(&d);
	// mlx_loop_hook(d.mlx, ft_hook, d.mlx);
	mlx_loop(d.mlx);
	mlx_terminate(d.mlx);
	system("leaks minirt");
	return (EXIT_SUCCESS);
}
