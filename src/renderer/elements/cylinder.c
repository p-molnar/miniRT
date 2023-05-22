/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 10:59:42 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/22 13:08:57 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

long double	yield_smallest_positive(long double *arr)
{
	int	i;
	long double	smallest;

	smallest = (unsigned int) -1;
	i = 0;	
	while (i < 4)
	{
		if (arr[i] > 0 && arr[i] < smallest)
			smallest = arr[i];
		i++;
	}
	if (smallest == (unsigned int) -1)
		smallest = -1;
	return (smallest);
}

long double	get_cylinder_intersection(long double *origin, t_vec3 *dir, t_scn_el *obj)
{
	long double	param[3];
	long double *t;
	long double	z[2];
	long double	intersect[4] = {-1, -1, -1, -1};
	long double	r;

	param[0] = pow(dir->coord[X], 2) + pow(dir->coord[Y], 2);
	param[1] = 2 * origin[X] * dir->coord[X] + 2 * origin[Y] * dir->coord[Y];
	param[2] = pow(origin[X], 2) + pow(origin[Y], 2) - pow(obj->diameter / 2, 2);
	t = quad_eq_solver(param[0], param[1], param[2], NULL);
	if (t != NULL)
	{
		ft_memcpy(intersect, t, 2 * sizeof(long double));
		z[0] = origin[Z] + t[0] * dir->coord[Z];
		z[1] = origin[Z] + t[1] * dir->coord[Z];
		if (!(z[0] > obj->cap[0].coord[Z] && z[0] < obj->cap[1].coord[Z]))
			intersect[0] = -1;
		if (!(z[1] > obj->cap[0].coord[Z] && z[1] < obj->cap[1].coord[Z]))
			intersect[1] = -1;
		free(t);
	}
	intersect[2] = get_plane_intersection(origin, dir, &obj->cap[0]);
	long double x = origin[X] + intersect[2] * dir->coord[X];
	long double y = origin[Y] + intersect[2] * dir->coord[Y];
	if (pow(x, 2) + pow(y, 2) >= pow(obj->diameter / 2, 2))
		intersect[2] = -1;
	intersect[3] = get_plane_intersection(origin, dir, &obj->cap[1]);
	x = origin[X] + intersect[3] * dir->coord[X];
	y = origin[Y] + intersect[3] * dir->coord[Y];
	if (pow(x, 2) + pow(y, 2) >= pow(obj->diameter / 2, 2))
		intersect[3] = -1;
	r = yield_smallest_positive(intersect);
	// printf("1: %Lf, 2: %Lf, 3: %Lf, 4: %Lf\n", intersect[0], intersect[1], intersect[2], intersect[3]);
	// printf("r: %Lf\n", r);
	return (r);
}
