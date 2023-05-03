/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:00:14 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/03 14:11:39 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <MLX42.h>
#include <math.h>
#include <minirt.h>
#include <mrt_data_struct.h>
#include <mrt_macros.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	init_scene(t_data *scn)
{
	ft_memset(scn, 0, sizeof(t_data));
}

void	print_scene_el(t_data *scn)
{
	t_list	*scn_el;
	char	*e[65];

	e[AMB_LIGHT] = "AMB";
	e[CAM] = "CAM";
	e[LIGHT] = "point light";
	e[DIR_LIGHT] = "Dir light";
	e[SPHERE] = "Sphere";
	e[PLANE] = "plane";
	e[CYLINDER] = "cylinder";
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
		printf("norm_vec: x=%Lf, y=%Lf, z=%Lf\n",
				el->norm_vec[0],
				el->norm_vec[1],
				el->norm_vec[2]);
		printf("diameter: %Lf\n", el->diameter);
		printf("radius: %Lf\n", el->radius);
		printf("height: %Lf\n", el->height);
		printf("fov: %Lf\n", el->fov);
		printf("intensity: %Lf\n", el->intensity);
		printf("specular: %Lf\n", el->specular);
		printf("color: r=%d, g=%d, b=%d, a=%d\n",
			get_color(el->color, R),
			get_color(el->color, G),
			get_color(el->color, B),
			get_color(el->color, A));
		scn_el = scn_el->next;
	}
}

void	create_projection_plane(t_data *d)
{
	long double	proj_plane_d;
	long double	proj_plane_side_len;
	long double	fov_rad;
	t_scn_el	**cam;

	proj_plane_d = 1;
	cam = get_scn_els(d->scn_el, CAM);
	if (!cam)
		error(ft_strdup("No camera found\n"), EXIT, 1);
	fov_rad = deg_to_rad(cam[0]->fov / 2.0);
	proj_plane_side_len = tan(fov_rad) * (2.0 * proj_plane_d);
	d->viewport[X] = proj_plane_side_len;
	d->viewport[Y] = proj_plane_side_len;
	free(cam);
}

void	set_up_vars(t_data *d)
{
	t_list		*ptr;
	t_scn_el	*obj;
	t_scn_el	**cam;

	ptr = d->scn_el;
	while (ptr)
	{
		obj = ptr->content;
		obj->radius = obj->diameter / 2;
		ptr = ptr->next;
	}
	cam = get_scn_els(d->scn_el, CAM);
	if (cam)
		d->cam = cam[0];
}

int	main(int argc, char *argv[])
{
	t_data	d;

	init_scene(&d);
	parse_scene(&d, argc, argv);
	set_up_vars(&d);
	create_projection_plane(&d);
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
