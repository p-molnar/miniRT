/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 10:59:42 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/10 11:03:18 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>

long double	*get_cylinder_intersection(t_data *data, t_scn_el *obj)
{
	long double	*t;
	long double	a;
	long double	b;
	long double	c;
	long double *r;

	r = ft_calloc(2, sizeof(long double));
	a = pow(data->vec[D]->coord[X], 2) + pow(data->vec[D]->coord[Y], 2);
	b = 2 * data->cam->coord[X] * data->vec[D]->coord[X] + 2 * data->cam->coord[Y] * data->vec[D]->coord[Y];
	c = pow(data->cam->coord[X], 2) + pow(data->cam->coord[Y], 2) - obj->diameter / 2;
	t = quad_eq_solver(a, b, c, NULL);
	if (!t)
		return (r);
	long double z1 = data->cam->coord[Z] + t[0] * data->vec[D]->coord[Z];
	long double z2 = data->cam->coord[Z] + t[1] * data->vec[D]->coord[Z];
	if (3 < z1 && z1 < 13)
		r[0] = t[0];
	if (3 < z2 && z2 < 13)
		r[1] = t[1];
	return (r);
}