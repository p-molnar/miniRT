/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   specular_lighting.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 09:50:16 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/30 16:38:17 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdio.h>

long double	get_specular_lighting(t_vec3 *dir, t_vec3 *light, t_vec3 *obj_norm, long double intensity, long double spec)
{
	long double	r_intensity;
	long double	dot_prod;
	t_vec3 		*scaled_norm;
	t_vec3 		*inverse_dir;
	t_vec3 		*vec_r;

	r_intensity = 0;
	scaled_norm = scale(2 * dot(obj_norm, light), obj_norm);
	vec_r = subtract(scaled_norm, light);
	inverse_dir = scale(-1, dir);
	dot_prod = dot(vec_r, inverse_dir);
	if (dot_prod > 0)
		r_intensity += intensity * pow(dot_prod / (vec_r->len
					* inverse_dir->len), spec);
	return (r_intensity);
}
