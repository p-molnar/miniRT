/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:00:14 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/21 12:12:53 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mrt_macros.h>
#include <MLX42.h>
#include <mrt_data_struct.h>
#include <stdlib.h>
#include <stdio.h>

#define WIDTH  256
#define HEIGHT 256


void	init_scene(t_data *scn)
{
	scn->scn_el = NULL;
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
		printf("coord: x=%f, y=%f, z=%f\n", ((t_scn_el *)el->content)->coord[0],
			((t_scn_el *)el->content)->coord[1],
			((t_scn_el *)el->content)->coord[2]);
		printf("norm_vec: x=%f, y=%f, z=%f\n",
			((t_scn_el *)el->content)->norm_vec[0],
			((t_scn_el *)el->content)->norm_vec[1],
			((t_scn_el *)el->content)->norm_vec[2]);
		printf("diameter: %f\n", ((t_scn_el *)el->content)->diameter);
		printf("height: %f\n", ((t_scn_el *)el->content)->height);
		printf("fov: %f\n", ((t_scn_el *)el->content)->fov);
		printf("brightness: %f\n", ((t_scn_el *)el->content)->brightness);
		printf("color: x=%d, y=%d, z=%d\n", ((t_scn_el *)el->content)->color[0],
			((t_scn_el *)el->content)->color[1],
			((t_scn_el *)el->content)->color[2]);
		el = el->next;
	}
}

int	main(int argc, char *argv[])
{
	t_data	d;

	init_scene(&d);
	parse_scene(&d, argc, argv);
	d.mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	if (!d.mlx)
		error(ft_strdup("MLX ERROR"), EXIT, 1);
	// print_scene_el(&scn);	
	// system("leaks minirt");
	return (EXIT_SUCCESS);
}
