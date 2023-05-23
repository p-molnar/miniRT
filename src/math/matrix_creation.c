/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix_creation.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/23 13:36:54 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/23 13:48:19 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

t_mx4	*create_scale_mx(t_coord3 x, t_coord3 y, t_coord3 z)
{
	t_mx4	*mx;

	mx = ft_calloc(4 * 4, sizeof(t_coord3));
	if (!mx)
		return (NULL);
	mx[0] = x;
	mx[5] = y;
	mx[10] = z;
	mx[15] = 1;
	return (mx);
}

t_mx4	*create_translation_mx(long double translation, t_coord3 x, t_coord3 y, t_coord3 z)
{
	t_mx4	*mx;

	mx = ft_calloc(4 * 4, sizeof(t_coord3));
	if (!mx)
		return (NULL);
	mx[0] = 1;
	mx[5] = 1;
	mx[10] = 1;
	mx[15] = 1;
	mx[3] = translation * x;
	mx[6] = translation * y;
	mx[9] = translation * z;
	return (mx);
}

t_mx4	*create_rotation_mx(long double rotation)
{
	t_mx4	*mx;

	mx = ft_calloc(4 * 4, sizeof(t_coord3));
	if (!mx)
		return (NULL);
	mx[0] = 1;
	mx[15] = 1;
	mx[5] = cos(rotation);
	mx[6] = -1 * sin(rotation);
	mx[10] = sin(rotation);
	mx[11] = cos(rotation);
	return (mx);
}

t_mx3	*create_rotation_mx3(long double theta, t_vec3 *axis)
{
	long double	sin_t;
	long double	cos_t;
	t_coord3	*u;
	t_mx3		*mx;

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