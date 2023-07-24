/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_color.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 15:57:27 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/24 16:09:25 by pmolnar       ########   odam.nl         */
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

t_color	get_local_color(t_data *data, t_ray ray, t_ray reflection_ray,
		t_scn_el closest_el)
{
	t_color		tmp_color;
	t_color		color;
	long double	intensity;
	int			i;

	intensity = get_lighting_intensity(data, ray, reflection_ray, closest_el);
	color = 0xFFFFFFFF;
	i = 1;
	while (i < COLOR_SIZE)
	{
		tmp_color = get_color(closest_el.color, i);
		color = update_color_channel(color, tmp_color * intensity, i);
		i++;
	}
	return (color);
}

t_color	get_reflected_color(t_data *data, t_ray ray, t_ray sec_ray, int depth)
{
	t_color		reflected_color;
	t_ray		reflected_ray;

	reflected_ray.origin = sec_ray.origin;
	reflected_ray.dir = get_reflection_ray(scale(-1, ray.dir), sec_ray.dir);
	reflected_color = trace_ray(data, reflected_ray, (t_range){EPS, INF}, depth
			- 1);
	return (reflected_color);
}
