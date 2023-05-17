/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix_ops.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/10 11:10:49 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/17 14:13:16 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>
#include <math.h>

t_vec3	*vec_times_mx(t_vec3 *vec, long double *mx, int mx_dimension)
{
	long double new_coords[3];
	long double sum;
	int i;
	int j;

	sum = 0;
	i = 0;
	j = 0;
	while (i < mx_dimension)
	{
		sum += mx[i] * vec->coord[i % 3];
		if ((i + 1) % 3 == 0)
		{
			new_coords[j++] = sum;
			sum = 0;
		}
		i++;
	}
	return (create_vec(NULL, new_coords));
}

long double	*create_rotation_mx(long double theta, t_vec3 *axis)
{
	long double	sin_t;
	long double	cos_t;
	long double	*u;
	long double	*mx;

	sin_t = sin(deg_to_rad(theta));
	cos_t = cos(deg_to_rad(theta));
	u = axis->n_coord;
	mx = malloc(9 * sizeof(long double));
	mx[0] = cos_t + pow(u[0], 2) * (1 - cos_t);
	mx[1] = u[0] * u[1] * (1 - cos_t) - u[2] * sin_t;
	mx[2] = u[0] * u[2] * (1 - cos_t) + u[1] * sin_t;
	mx[3] = u[1] * u[0] * (1 - cos_t) + u[2] * sin_t;
	mx[4] = cos_t + pow(u[1], 2) * (1 - cos_t);
	mx[5] = u[1] * u[2] * (1 - cos_t) - u[0] * sin_t;
	mx[6] = u[2] * u[0] * (1 - cos_t) - u[1] * sin_t;
	mx[7] = u[2] * u[1] * (1 - cos_t) + u[0] * sin_t;
	mx[8] = cos_t + pow(u[2], 2) * (1 - cos_t);
	return (mx);
}