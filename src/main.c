/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:00:14 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/01 22:02:26 by pmolnar       ########   odam.nl         */
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
	// scn->bg = 0xa3c4c0FF;
	scn->bg = 0xFFFFFFFF;
	// scn->bg = 0x000000FF;
}

void	print_scene_el(t_data *scn)
{
	t_list	*el;

	el = NULL;
	if (scn)
		el = scn->scn_el;
	while (el)
	{
		printf("- - - - - - - - - - - - - - - - - -\n");
		printf("type: %d\n", ((t_scn_el *)el->content)->type);
		printf("coord: x=%Lf, y=%Lf, z=%Lf\n", ((t_scn_el *)el->content)->coord[0],
				((t_scn_el *)el->content)->coord[1],
				((t_scn_el *)el->content)->coord[2]);
		printf("norm_vec: x=%Lf, y=%Lf, z=%Lf\n",
				((t_scn_el *)el->content)->norm_vec[0],
				((t_scn_el *)el->content)->norm_vec[1],
				((t_scn_el *)el->content)->norm_vec[2]);
		printf("diameter: %Lf\n", ((t_scn_el *)el->content)->diameter);
		printf("height: %Lf\n", ((t_scn_el *)el->content)->height);
		printf("fov: %Lf\n", ((t_scn_el *)el->content)->fov);
		printf("intensity: %Lf\n", ((t_scn_el *)el->content)->intensity);
		// printf("color: r=%d, g=%d, b=%d, a=%d\n",
		// 	get_r(((t_scn_el *)el->content)->color),
		// 	get_g(((t_scn_el *)el->content)->color),
		// 	get_b(((t_scn_el *)el->content)->color),
		// 	get_a(((t_scn_el *)el->content)->color));
		el = el->next;
	}
}

void	create_projection_plane(t_data *d)
{
	long double		proj_plane_d;
	long double		proj_plane_side_len;
	long double		fov_rad;
	t_scn_el		**cam;

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
	// print_scene_el(&d);
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
