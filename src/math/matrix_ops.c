/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   matrix_ops.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 15:01:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/28 13:11:07 by pmolnar       ########   odam.nl         */
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

	if (!init_point || !terminal_point)
		return (NULL);
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

t_vec	*scale_vec(long double scaler, t_vec *vec)
{
	t_vec	*new_vec;
	int		i;

	new_vec = ft_calloc(1, sizeof(t_vec));
	if (!new_vec)
		return (NULL);
	i = 0;
	while (i < COORD_SIZE && vec)
	{
		new_vec->coord[i] = scaler * vec->coord[i];
		i++;
	}
	compute_vec_len(new_vec);
	compute_normal_vec(new_vec);
	return (new_vec);
}

long double	dot(t_vec *vec_1, t_vec *vec_2)
{
	long double	result;
	int			i;

	result = 0;
	i = 0;
	while (i < COORD_SIZE)
	{
		result += vec_1->coord[i] * vec_2->coord[i];
		i++;
	}
	return (result);
}

t_vec	*addition(t_vec *vec_1, t_vec *vec_2)
{
	t_vec	*new_vec;
	int	i;

	new_vec = ft_calloc(1, sizeof(t_vec));
	if (!new_vec || !vec_1 || !vec_2)
		return (NULL);
	i = 0;
	while (i < COORD_SIZE)
	{
		new_vec->coord[i] = vec_1->coord[i] + vec_2->coord[i];
		i++;
	}
	compute_vec_len(new_vec);
	compute_normal_vec(new_vec);
	return (new_vec);
}