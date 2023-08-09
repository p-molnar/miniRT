/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 11:00:13 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/09 18:20:07 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>

long double	get_plane_intersection(t_ray ray, t_scn_el *obj)
{
	long double	t;
	long double	denominator;

	t = -1;
	denominator = dot(obj->orientation, ray.dir);
	if (fabsl(denominator) > 0.0)
		t = dot(obj->orientation, 
				create_dir_vec(ray.origin, obj->pos)) / denominator;
	return (t);
}
