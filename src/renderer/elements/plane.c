/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 11:00:13 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/09 14:50:43 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>
#include <stdlib.h>

long double	get_plane_intersection(t_ray *ray, t_scn_el *obj)
{
	long double	t;
	t_vec3		*EQ;
	long double	denom;

	t = -1;
	EQ = create_dir_vec(*ray->origin, obj->pos);
	denom = dot(obj->n_vec, ray->dir);
	if (fabsl(denom) > EPS)
		t = dot(obj->n_vec, EQ) / denom;
	return (t);
}