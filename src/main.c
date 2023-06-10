/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:00:14 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/10 15:25:52 by pmolnar       ########   odam.nl         */
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
	d->scn_el[AMB_LIGHT] = get_scn_els(d->all_scn_el, F_AMB_LIGHT);
	d->scn_el[CAM] = get_scn_els(d->all_scn_el, F_CAM | F_TG_CAM);
	d->scn_el[POINT_LIGHT] = get_scn_els(d->all_scn_el, F_POINT_LIGHT);
	d->scn_el[DIR_LIGHT] = get_scn_els(d->all_scn_el, F_DIR_LIGHT);
	d->scn_el[SPHERE] = get_scn_els(d->all_scn_el, F_SPHERE);
	d->scn_el[PLANE] = get_scn_els(d->all_scn_el, F_PLANE);
	d->scn_el[CYLINDER] = get_scn_els(d->all_scn_el, F_CYLINDER);
	d->scn_el[CYLINDER_CAP] = get_scn_els(d->all_scn_el, F_CYLINDER_CAP);
	d->grp_scn_el[LIGHTS] = get_scn_els(d->all_scn_el, G_LIGHTS);
	d->grp_scn_el[OBJS] = get_scn_els(d->all_scn_el, G_OBJS);
}

int	main(int argc, char *argv[])
{
	(void) argc, (void) argv;
	// t_coord3 a, b;
	// a.x = 1;
	// a.y = 2;
	// a.z = 3;
	// b.x = 5;
	// b.y = 2;
	// b.z = 0;
	// t_vec3 *c = create_vec(a.x, a.y, a.z);
	// t_vec3 *d = get_normal_vec(c);
	// printf("c: %Lf", c->len);
	// printf("d: %Lf", d->len);
	t_data	d;

	ft_memset(&d, 0, sizeof(t_data));
	parse_input(&d, argc, argv);
	set_up_variables(&d);
	set_up_camera(&d);
	t_list *ptr = d.all_scn_el;
	while (ptr)
	{
		print_scene_el(ptr->content);
		ptr = ptr->next;
	}
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