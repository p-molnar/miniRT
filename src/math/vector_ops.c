/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_ops.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 15:01:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/02 10:41:46 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mrt_macros.h>

#include <math.h>
#include <stdlib.h>

t_vec	*create_vec(long double *init_point, long double *terminal_point)
{
	t_vec				*vec;
	int					i;
	const long double	origin[3] = {0, 0, 0};

	if (!terminal_point)
		return (NULL);
	if (init_point == NULL)
		init_point = (long double *)origin;
	vec = ft_calloc(1, sizeof(t_vec));
	if (!vec)
		return (NULL);
	i = 0;
	while (i < COORD_SIZE)
	{
		vec->coord[i] = terminal_point[i] - init_point[i];
		i++;
	}
	compute_vec_len(vec);
	compute_normal_vec(vec);
	return (vec);
}

void	compute_vec_len(t_vec *vec)
{
	long double	sum_of_sqrs;
	int			i;

	sum_of_sqrs = 0;
	i = 0;
	while (i < COORD_SIZE)
	{
		sum_of_sqrs += pow(vec->coord[i], 2);
		i++;
	}
	vec->len = sqrt(sum_of_sqrs);
}

void	compute_normal_vec(t_vec *vec)
{
	int	i;

	i = 0;
	while (i < COORD_SIZE && vec)
	{
		vec->n_coord[i] = vec->coord[i] / vec->len;
		i++;
	}
}

void	normalize_vec(t_vec *vec)
{
	int	i;

	i = 0;
	while (i < COORD_SIZE && vec)
	{
		vec->coord[i] = vec->n_coord[i];
		i++;
	}
	compute_vec_len(vec);
}
