/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   specular_lighting.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 09:50:16 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/06/10 15:27:21 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdio.h>

long double	get_specular_lighting(t_ray *ray, t_ray *secondary_ray, t_vec3 *obj_norm,
				long double intensity, long double spec)
{
	long double	r_intensity;
	long double	dot_prod;
	t_vec3 		*scaled_norm;
	t_vec3 		*inverse_dir;
	t_vec3 		*vec_r;

	// printf("specular lighting\n");
	r_intensity = 0;
	scaled_norm = scale(2 * dot(obj_norm, secondary_ray->dir), obj_norm);
	vec_r = subtract(scaled_norm, secondary_ray->dir);
	inverse_dir = scale(-1, ray->dir);
	dot_prod = dot(vec_r, inverse_dir);
	// printf("dot: %Lf\n", dot_prod);
	if (dot_prod > 0)
	{
		r_intensity += intensity * pow(dot_prod / (vec_r->len
					* inverse_dir->len), spec);
		// printf("rint: %Lf\n", r_intensity);
	}
	return (r_intensity);
}
