/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   specular_lighting.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 09:50:16 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/23 00:23:05 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdlib.h>

long double	get_specular_intensity(t_ray *rays,
		long double intensity, long double spec)
{
	long double	r_intensity;
	long double	dot_prod;
	t_vec3		scaled_norm;
	t_vec3		inverse_dir;
	t_vec3		vec_r;

	r_intensity = 0;
	scaled_norm = scale(2 * dot(rays[1].dir, rays[3].dir), rays[1].dir);
	vec_r = vec_subtract(scaled_norm, rays[1].dir);
	inverse_dir = scale(-1, rays[0].dir);
	dot_prod = dot(vec_r, inverse_dir);
	if (dot_prod > 0)
	{
		r_intensity += intensity * pow(dot_prod / (vec_r.len * inverse_dir.len),
				spec);
	}
	return (r_intensity);
}
