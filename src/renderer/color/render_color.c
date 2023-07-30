/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_color.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 15:57:27 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/30 15:35:40 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>

t_vec3	get_reflection_ray(t_vec3 ray, t_vec3 norm)
{
	t_vec3	scaled_vec;
	t_vec3	scaled_minus_ray;

	scaled_vec = scale(2 * dot(ray, norm), norm);
	scaled_minus_ray = vec_subtract(scaled_vec, ray);
	return (scaled_minus_ray);
}

t_color	get_reflected_color(t_data *data, t_ray ray, t_hit_obj hit_obj, int depth)
{
	t_color		reflected_color;
	t_ray		reflected_ray;

	reflected_ray.origin = hit_obj.inc_p;
	reflected_ray.dir = get_reflection_ray(scale(-1, ray.dir), hit_obj.norm);
	reflected_color = trace_ray(data, reflected_ray, (t_range){EPS, INF}, depth
			- 1);
	return (reflected_color);
}
