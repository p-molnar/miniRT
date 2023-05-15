/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:00:14 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/10 11:28:59 by pmolnar       ########   odam.nl         */
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
		if (el->n_vec)
		{
			printf("norm_vec: x=%Lf, y=%Lf, z=%Lf\n",
					el->n_vec->n_coord[0],
					el->n_vec->n_coord[1],
					el->n_vec->n_coord[2]);
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
		scn_el = scn_el->next;
	}
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
