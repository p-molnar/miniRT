/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 10:59:42 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/15 22:21:17 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>
#include <stdio.h>

long double	*get_cylinder_intersection(t_data *data, long double *origin, t_scn_el *obj)
{
	long double	param[3];
	long double *t;
	long double	end[2];
	long double	z[2];

	end[0] = obj->coord[Z] - obj->height / 2;
	end[1] = obj->coord[Z] + obj->height / 2;
	param[0] = pow(data->vec[D]->coord[X], 2) + pow(data->vec[D]->coord[Y], 2);
	param[1] = 2 * origin[X] * data->vec[D]->coord[X] + 2 * origin[Y] * data->vec[D]->coord[Y];
	param[2] = pow(origin[X], 2) + pow(origin[Y], 2) - 1;
	t = quad_eq_solver(param[0], param[1], param[2], NULL);
	if (t != NULL)
	{
		z[0] = origin[Z] + t[0] * data->vec[D]->coord[Z];
		z[1] = origin[Z] + t[1] * data->vec[D]->coord[Z];
		t[0] = 0;
		t[1] = 0;
		if (z[0] >= end[0])
			t[0] = (end[0] - origin[Z]) / data->vec[D]->coord[Z];
		if (z[1] >= end[1])
			t[1] = (end[1] - origin[Z]) / data->vec[D]->coord[Z];
	}
	return (t);
}
