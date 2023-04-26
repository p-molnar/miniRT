/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix_ops.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 15:01:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/26 14:08:41 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <mrt_data_struct.h>
#include <mrt_macros.h>

t_vec	*get_dir_vec(long double *init_point, long double *terminal_point)
{
	t_vec				*vec;
	int					i;
	long double			sum_of_sqrs;

	vec = ft_calloc(1, sizeof(t_vec));
	if (!vec)
		return (NULL);
	sum_of_sqrs = 0;
	i = 0;
	while (i < COORD_SIZE)
	{
		vec->coord[i] = terminal_point[i] - init_point[i];
		sum_of_sqrs += pow(vec->coord[i], 2);
		i++;
	}
	vec->len = sqrt(sum_of_sqrs);
	i = 0;
	while (i < COORD_SIZE)
	{
		vec->n_coord[i] = vec->coord[i] / vec->len;
		i++;
	}
	return (vec);
}

// long double	*get_normal_vec(t_vec *vec)
// {
// 	long double	*coord;
// 	long double	vec_len;
// 	int			i;

// 	coord = malloc(1 * sizeof(long double));
// 	if (!coord)
// 		return (NULL);
// 	vec_len = vec->len;
// 	i = 0;
// 	while (i < COORD_SIZE)
// 	{
// 		coord[i] = vec->coord[i] / vec_len;
// 		i++;
// 	}
// 	return (coord);
// }

long double	dot(t_vec *vec_1, t_vec *vec_2)
{
	long double	result;

	result = vec_1->coord[X] * vec_2->coord[X] + vec_1->coord[Y]
		* vec_2->coord[Y] + vec_1->coord[Z] * vec_2->coord[Z];
	return (result);
}
