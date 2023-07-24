/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 11:00:13 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/21 16:42:55 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>
#include <stdlib.h>

long double	get_plane_intersection(t_ray ray, t_scn_el *obj)
{
	long double	t;
	long double	denominator;

	t = -1;
	denominator = dot(obj->n_vec, ray.dir);
	if (fabsl(denominator) > 0.0)
		t = dot(obj->n_vec, create_dir_vec(ray.origin, obj->pos)) / denominator;
	return (t);
}
