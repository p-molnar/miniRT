/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   specular_lighting.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 09:50:16 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/17 12:21:21 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>

long double	get_specular_lighting(t_data *data, t_scn_el *light,
		long double specular)
{
	long double	intensity;
	long double	dot_prod;
	t_vec3 		*scaled_norm;
	t_vec3 		*inverse_dir;
	t_vec3 		*vec_r;

	intensity = 0;
	scaled_norm = scale(2 * dot(data->vec[N], data->vec[L]), data->vec[N]);
	vec_r = subtract(scaled_norm, data->vec[L]);
	inverse_dir = scale(-1, data->vec[D]);
	dot_prod = dot(vec_r, inverse_dir);
	if (dot_prod > 0)
		intensity += light->intensity * pow(dot_prod / (vec_r->len
					* inverse_dir->len), specular);
	return (intensity);
}
