/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer_util.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 15:55:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/12 17:55:11 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

t_coord3	*get_incident_point(t_ray *ray, t_closest *obj)
{
	t_coord3	*inc_p;

	inc_p = offset(ray->origin, scale(obj->dist, ray->dir));
	printf("inc_P: %Lf, %Lf, %Lf\n", inc_p->x, inc_p->y, inc_p->z);
	return (inc_p);
}

t_closest	*get_closest_el(t_scn_el **el, t_ray *ray, const long double *range)
{
	t_closest	*closest;
	long double	t;
	int			i;

	closest = malloc(sizeof(t_closest));
	if (!closest)
		return (NULL);
	closest->el = NULL;
	closest->dist = INF;
	i = 0;
	while (el && el[i])
	{
		if (el[i]->type == F_SPHERE)
			t = get_sphere_intersections(ray, el[i]);
		else if (el[i]->type == F_CYLINDER)
			t = get_cylinder_intersection(ray, el[i]);
		else if (el[i]->type == F_PLANE)
			t = get_plane_intersection(ray, el[i]);
		if (is_in_range_f(t, range[MIN], range[MAX]) && t < closest->dist)
		{
			closest->dist = t;
			closest->el = el[i];
		}
		if (is_in_range_f(t, range[MIN], range[MAX]) && t < closest->dist)
		{
			closest->dist = t;
			closest->el = el[i];
		}
		i++;
	}
	return (closest);
}

t_vec3	*get_ray_reflection(t_vec3 *ray, t_vec3 *norm)
{
	long double	ray_dot_norm;
	t_vec3		*scaled_vec;
	t_vec3		*scaled_minus_ray;

	if (!ray || !norm)
		return (NULL);
	ray_dot_norm = 2 * dot(ray, norm);
	scaled_vec = scale(ray_dot_norm, norm);
	scaled_minus_ray = subtract(scaled_vec, ray);
	free(scaled_vec);
	return (scaled_minus_ray);
}