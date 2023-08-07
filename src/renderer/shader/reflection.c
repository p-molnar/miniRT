/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reflection.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/30 16:01:31 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/07 12:48:17 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_color	get_reflected_color(t_data *data, t_ray ray, t_hit_obj hit_obj,
		int refl_recursion)
{
	long double	agl;
	t_vec3		reflection;
	t_color		hit_color;

	if (hit_obj.attr->refl_coeff <= 0 || refl_recursion <= 0)
		return ((t_color){.color = BACKGROUND_COLOR});
	agl = dot(hit_obj.norm, ray.dir);
	reflection = subtract_vec(ray.dir, scale_vec(2 * agl, hit_obj.norm));
	normalize_vec(&reflection);
	hit_color = trace_ray(data, (t_ray){hit_obj.inc_p, reflection},
			(t_range){EPS, INF}, refl_recursion - 1);
	return (hit_color);
}
