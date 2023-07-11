/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:00:14 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/11 14:08:31 by pmolnar       ########   odam.nl         */
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

void	clean_up(t_data *d)
{
	int			i;
	t_list	*next;

	while (d->all_scn_el)
	{
		next = d->all_scn_el->next;
		free_scn_el(d->all_scn_el->content);
		free(d->all_scn_el);
		d->all_scn_el = next;
	}
	i = 0;
	while (i < SCN_SIZE)
		free(d->scn_els[i++]);
	free_mx(d->ctw_mx);
	free(d->dft_world_orientation);
	free(d->dft_up_vec);
}

int	main(int argc, char *argv[])
{
	t_data	d;

	ft_memset(&d, 0, sizeof(t_data));
	d.dft_world_orientation  = create_vec(0, 0, 1);
	d.dft_up_vec = create_vec(0, 1, 0);
	parse_input(&d, argc, argv);
	set_up_variables(&d);
	set_up_camera(&d);
	d.mlx = mlx_init(CANVAS_W + 5, CANVAS_H + 5, "MiniRT", true);
	if (!d.mlx)
		error(ft_strdup(mlx_strerror(mlx_errno)), EXIT, 1);
	d.img = mlx_new_image(d.mlx, CANVAS_W, CANVAS_H);
	if (!d.img || (mlx_image_to_window(d.mlx, d.img, 0, 0) < 0))
		error(ft_strdup(mlx_strerror(mlx_errno)), EXIT, 1);
	render_scene(&d);
	clean_up(&d);
	// mlx_loop_hook(d.mlx, ft_hook, d.mlx);
	mlx_loop(d.mlx);
	mlx_terminate(d.mlx);
	system("leaks minirt");
	return (EXIT_SUCCESS);
}