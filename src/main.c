/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:00:14 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/24 23:10:45 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	print_scene_el(t_data *scn)
{
	t_list	*scn_el;
	char	*e[SCN_SIZE];

	e[AMB_LIGHT] = "AMB";
	e[CAM] = "CAM";
	e[POINT_LIGHT] = "point light";
	e[DIR_LIGHT] = "Dir light";
	e[SPHERE] = "Sphere";
	e[PLANE] = "plane";
	e[CYLINDER] = "cylinder";
	e[CYLINDER_CAP] = "cylinder cap";
	scn_el = scn->scn_el;
	while (scn_el)
	{
		t_scn_el *el = scn_el->content;
		printf("- - - - - - - - - - - - - - - - - -\n");
		printf("type: %s\n", e[el->type]);
		printf("coord: x=%Lf, y=%Lf, z=%Lf\n",
				el->coord[0],
				el->coord[1],
				el->coord[2]);
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
		scn_el = scn_el->next;
	}
}

void	populate_cylinder_properties(t_scn_el *pl, t_scn_el *cy, char cap_type)
{
	int			is_btm;
	t_coord3	*term;

	is_btm = cap_type == 'B';
	pl->type = CYLINDER_CAP;
	pl->color = cy->color;
	pl->reflection = cy->reflection;
	pl->specular = cy->specular;
	ft_memcpy(pl->coord, cy->coord, COORD_SIZE * sizeof(long double));
	if (is_btm)
	{
		pl->coord[Z] = cy->coord[Z] - cy->height / 2;
		term = create_coord(pl->coord[X], pl->coord[Y], pl->coord[Z] - 1);
	}
	else
	{
		pl->coord[Z] = cy->coord[Z] + cy->height / 2;
		term = create_coord(pl->coord[X], pl->coord[Y], pl->coord[Z] + 1);
	}
	pl->n_vec = create_vec(pl->coord, term);
}

void	add_cylinder_caps(t_scn_el **cy)
{
	t_scn_el	*caps;
	int			i;

	i = 0;	
	while (cy && cy[i])
	{
		caps = ft_calloc(2, sizeof(t_scn_el));
		populate_cylinder_properties(&caps[0], cy[i], 'B');
		populate_cylinder_properties(&caps[1], cy[i], 'T');
		cy[i]->cap = caps;
		i++;
	}	
	free(cy);
}

int	main(int argc, char *argv[])
{
	(void) argc, (void) argv;
	// t_mx mx1;
	// t_mx mx2;
	// mx1.c = 4;
	// mx1.r = 4;
	// long double m1[16] = {5, 8, 1, 5, 12, -5, -6, 8, 4, 12, -6, 0, -7.5, 9, 0, 5};
	// mx1.m = m1;
	// long double m2[16] = {5, 8, 32, -234.5, 23, -67.2, 28, 6, 8, 4, -22.2, 3,-1523, -2151, -61, 0};
	// mx2.c = 4;
	// mx2.r = 4;
	// mx2.m = m2;
	// t_mx *mx_m = multiply_mx(&mx1, &mx2);
	// printf("[\n");
	// for (int i = 0; i < 16; i++)
	// {
	// 	printf("%Lf  ", mx_m->m[i]);
	// 	if (!((i + 1) % 4))
	// 		printf("\n");
	// }
	// printf("]\n");
	t_data	d;

	init_scene(&d);
	parse_scene(&d, argc, argv);
	set_up_vars(&d);
	create_projection_plane(&d);
	add_cylinder_caps(get_scn_els(d.scn_el, CYLINDER));
	print_scene_el(&d);
	d.mlx = mlx_init(CANVAS_W + 5, CANVAS_H + 5, "MiniRT", true);
	if (!d.mlx)
		error(ft_strdup(mlx_strerror(mlx_errno)), EXIT, 1);
	d.img = mlx_new_image(d.mlx, CANVAS_W, CANVAS_H);
	if (!d.img || (mlx_image_to_window(d.mlx, d.img, 0, 0) < 0))
		error(ft_strdup(mlx_strerror(mlx_errno)), EXIT, 1);
	render_img(&d);
	// mlx_loop_hook(d.mlx, ft_hook, d.mlx);
	mlx_loop(d.mlx);
	mlx_terminate(d.mlx);
	// system("leaks minirt");
	return (EXIT_SUCCESS);
}
