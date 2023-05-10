/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   specular_lighting.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 09:50:16 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/10 10:37:32 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>

long double	get_specular_lighting(t_vec3 **vec, t_scn_el *light,
		long double specular)
{
	long double intensity;
	long double n_dot_l;
	long double rv_dot_v;
	t_vec3	*tmp_vec[VEC_SIZE];

	intensity = 0;
	if (specular != -1)
	{
		init_vec(tmp_vec, VEC_SIZE);
		n_dot_l = dot(vec[N], vec[L]);
		tmp_vec[Ns] = scale(2 * n_dot_l, vec[N]);
		tmp_vec[Rv] = subtract(vec[Ns], vec[L]);
		tmp_vec[V] = scale(-1, vec[Ds]);
		rv_dot_v = dot(tmp_vec[Rv], tmp_vec[V]);
		if (rv_dot_v > 0)
			intensity += light->intensity * pow(rv_dot_v
					/ (tmp_vec[Rv]->len * tmp_vec[V]->len), specular);
		free_vec(tmp_vec, VEC_SIZE);
	}
	return (intensity);
}