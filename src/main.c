/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:00:14 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/05 12:31:45 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	set_up_variables(t_data *d)
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
	d.dft_world_orientation  = create_vec(0, 0, 1);
	parse_input(&d, argc, argv);
	set_up_variables(&d);
	set_up_camera(&d);
	// t_list *ptr = d.all_scn_el;
	// while (ptr)
	// {
	// 	print_scene_el(ptr->content);
	// 	ptr = ptr->next;
	// }
	d.mlx = mlx_init(CANVAS_W + 5, CANVAS_H + 5, "MiniRT", true);
	if (!d.mlx)
		error(ft_strdup(mlx_strerror(mlx_errno)), EXIT, 1);
	d.img = mlx_new_image(d.mlx, CANVAS_W, CANVAS_H);
	if (!d.img || (mlx_image_to_window(d.mlx, d.img, 0, 0) < 0))
		error(ft_strdup(mlx_strerror(mlx_errno)), EXIT, 1);
	render_scene(&d);
	// mlx_loop_hook(d.mlx, ft_hook, d.mlx);
	mlx_loop(d.mlx);
	mlx_terminate(d.mlx);
	// system("leaks minirt");
	return (EXIT_SUCCESS);
}