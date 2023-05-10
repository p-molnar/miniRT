/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 11:00:13 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/10 11:03:09 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>
#include <stdlib.h>

long double	*get_plane_intersection(t_data *data, t_scn_el *obj)
{
	long double	*t;
	t_vec3		*Q;
	t_vec3		*E;
	t_vec3		*Q_less_E;
	long double	denom;

	t = malloc(2 * sizeof(long double));
	Q = create_vec(NULL, obj->coord);
	E = create_vec(NULL, data->cam->coord);
	Q_less_E = subtract(Q, E);
	denom = dot(obj->n_vec, data->vec[D]);
	if (fabs(denom) > 0.0001)
	{
		t[0] = dot(obj->n_vec, Q_less_E) / denom;
		t[1] = t[0];
	}
	else
	{
		t[0] = 0;
		t[1] = 0;
	}
	return (t);
}