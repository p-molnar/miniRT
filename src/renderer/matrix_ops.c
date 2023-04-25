/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix_ops.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 15:01:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/25 14:13:26 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mrt_data_struct.h>
#include <mrt_macros.h>
#include <math.h>

t_vec	*get_dir_vec(long double *init_point, long double *terminal_point)
{
	t_vec	*vec;

	vec = ft_calloc(1, sizeof(t_vec));
	if (!vec)
		return (NULL);
	vec->coord[X] = terminal_point[X] - init_point[X];
	vec->coord[Y] = terminal_point[Y] - init_point[Y];
	vec->coord[Z] = terminal_point[Z] - init_point[Z];
	vec->norm = sqrt(pow(vec->coord[X], 2) \
					+ pow(vec->coord[Y], 2) \
					+ pow(vec->coord[Z], 2));
	return (vec);
}

long double	dot(t_vec *vec_1, t_vec *vec_2)
{
	long double	result;

	result = vec_1->coord[X] * vec_2->coord[X] \
			+ vec_1->coord[Y] * vec_2->coord[Y] \
			+ vec_1->coord[Z] * vec_2->coord[Z];
	return (result);
}
