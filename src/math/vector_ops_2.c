/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_ops_2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/28 14:48:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/02 16:57:16 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>

t_vec	*scale(long double scaler, t_vec *vec)
{
	t_vec	*new;
	int	i;

	new = malloc(1 * sizeof(t_vec));
	if (!new)
		return (NULL);
	i = 0;
	while (i < COORD_SIZE && vec)
	{
		new->coord[i] = scaler * vec->coord[i];
		i++;
	}
	compute_vec_len(new);
	compute_normal_vec(new);
	return (new);
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

t_vec	*add(t_vec *vec_1, t_vec *vec_2)
{
	t_vec	*new_vec;
	int		i;

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

t_vec	*subtract(t_vec *vec_1, t_vec *vec_2)
{
	t_vec	*new;
	t_vec	*scaled_vec;

	if (!vec_1 || !vec_2)
		return (NULL);
	scaled_vec = scale(-1, vec_2);
	if (!scaled_vec)
		return (NULL);
	new = add(vec_1, scaled_vec);
	compute_vec_len(new);
	compute_normal_vec(new);
	free(scaled_vec);
	return (new);
}