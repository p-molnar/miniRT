/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   specular_lighting.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/03 09:50:16 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/03 09:57:46 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>

long double	get_specular_lighting(t_data *data, t_scn_el *light,
		long double specular)
{
	long double intensity;
	long double n_dot_l;
	long double rv_dot_v;

	intensity = 0;
	if (specular != -1)
	{
		n_dot_l = dot(data->vec[N], data->vec[L]);
		data->vec[Ns] = scale(2 * n_dot_l, data->vec[N]);
		data->vec[Rv] = subtract(data->vec[Ns], data->vec[L]);
		data->vec[V] = scale(-1, data->vec[Ds]);
		rv_dot_v = dot(data->vec[Rv], data->vec[V]);
		if (rv_dot_v > 0)
			intensity += light->intensity * pow(rv_dot_v
					/ (data->vec[Rv]->len * data->vec[V]->len), specular);
	}
	return (intensity);
}