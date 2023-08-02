/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printer.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 10:18:43 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/03 00:12:37 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdio.h>

void	print_mx(t_mx *mx)
{
	int	dim;

	printf("[\n");
	dim = mx->r * mx->c;
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
			el->pos.coord[0],
			el->pos.coord[1],
			el->pos.coord[2]);
	printf("target: x=%Lf, y=%Lf, z=%Lf\n",
			el->target.coord[0],
			el->target.coord[1],
			el->target.coord[2]);
	printf("n_vec->dir: x=%Lf, y=%Lf, z=%Lf\n",
			el->orientation.dir.coord[0],
			el->orientation.dir.coord[1],
			el->orientation.dir.coord[2]);
	printf("diameter: %Lf\n", el->diameter);
	printf("radius: %Lf\n", el->radius);
	printf("height: %Lf\n", el->height);
	printf("fov: %Lf\n", el->fov);
	printf("intensity: %Lf\n", el->intensity);
	printf("specular: %Lf\n", el->spec_coeff);
	printf("reflection: %Lf\n", el->refl_coeff);
	printf("color: r=%d, g=%d, b=%d, a=%d\n",
		el->color.r, 
		el->color.g, 
		el->color.b, 
		el->color.a); 
	if (el->cap)
	{
		print_scene_el(&el->cap[0]);
		print_scene_el(&el->cap[1]);
	}
}
