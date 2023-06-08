/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:00:14 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/08 10:04:05 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	print_scene_el(t_scn_el *el)
{
	char	*e[F_SCN_SIZE];

	e[F_AMB_LIGHT] = "AMB";
	e[F_CAM] = "CAM";
	e[F_TG_CAM] = "Target cam";
	e[F_POINT_LIGHT] = "point light";
	e[F_DIR_LIGHT] = "Dir light";
	e[F_SPHERE] = "Sphere";
	e[F_PLANE] = "plane";
	e[F_CYLINDER] = "cylinder";
	e[F_CYLINDER_CAP] = "cylinder cap";
	printf("- - - - - - - - - - - - - - - - - -\n");
	printf("type: %s\n", e[el->type]);
	printf("coord: x=%Lf, y=%Lf, z=%Lf\n",
			el->pos[0],
			el->pos[1],
			el->pos[2]);
	printf("tg_coord: x=%Lf, y=%Lf, z=%Lf\n",
			el->tg_coord[0],
			el->tg_coord[1],
			el->tg_coord[2]);
	if (el->n_vec)
	{
		printf("n_vec->dir: x=%Lf, y=%Lf, z=%Lf\n",
				el->n_vec->dir[0],
				el->n_vec->dir[1],
				el->n_vec->dir[2]);
	}
	printf("diameter: %Lf\n", el->diameter);
	printf("radius: %Lf\n", el->radius);
	printf("height: %Lf\n", el->height);
	printf("fov: %Lf\n", el->fov);
	printf("intensity: %Lf\n", el->intensity);
	printf("specular: %Lf\n", el->specular);
	printf("reflection: %Lf\n", el->reflection);
	printf("color: r=%d, g=%d, b=%d, a=%d\n",
		get_color(el->color, R),
		get_color(el->color, G),
		get_color(el->color, B),
		get_color(el->color, A));
	if (el->cap)
	{
		print_scene_el(&el->cap[0]);
		print_scene_el(&el->cap[1]);
	}
}

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
	d->scn_el[LIGHTS] = get_scn_els(d->all_scn_el, G_LIGHTS);
	d->scn_el[OBJS] = get_scn_els(d->all_scn_el, G_OBJS);
}

int	main(int argc, char *argv[])
{
	t_data	d;

	ft_memset(&d, 0, sizeof(t_data));
	parse_input(&d, argc, argv);
	set_up_variables(&d);
	t_list *ptr = d.all_scn_el;
	while (ptr)
	{
		print_scene_el(ptr->content);
		ptr = ptr->next;
	}
	set_up_scene(&d);
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
