/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printer.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 10:18:43 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/08 10:26:19 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdio.h>

void	print_mx(t_mx *mx)
{
	printf("[\n");
	int dim = mx->r * mx->c;
	for (int i = 0; i < dim; i++)
	{
		printf("% .4Lf   ", mx->m[i]);
		if (!((i + 1) % mx->c))
			printf("\n");
	}
	printf("]\n");
}

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
