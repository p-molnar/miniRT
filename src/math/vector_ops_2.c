/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_ops_2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/28 14:48:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/28 14:51:07 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	scale(long double scaler, t_vec *vec)
{
	int	i;

	i = 0;
	while (i < COORD_SIZE && vec)
	{
		vec->coord[i] = scaler * vec->coord[i];
		i++;
	}
	compute_vec_len(vec);
	compute_normal_vec(vec);
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
