/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 11:00:13 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/16 14:26:05 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>
#include <stdlib.h>

long double	get_plane_intersection(t_data *data, t_scn_el *obj)
{
	long double	t;
	t_vec3		*EQ;
	long double	denom;

	t = -1;
	EQ = create_vec(data->cam->coord, obj->coord);
	denom = dot(obj->n_vec, data->vec[D]);
	if (fabsl(denom) > 0.0001)
		t = dot(obj->n_vec, EQ) / denom;
	return (t);
}