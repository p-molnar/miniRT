/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_ops_2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/28 14:48:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/22 12:20:20 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>

t_vec3	*scale(long double scaler, t_vec3 *vec)
{
	t_vec3	*new;
	int		i;

	new = malloc(1 * sizeof(t_vec3));
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

long double	dot(t_vec3 *vec_1, t_vec3 *vec_2)
{
	long double	result;
	int			i;

	result = 0;
	i = 0;
	while (i < COORD_SIZE && vec_1 && vec_2)
	{
		result += vec_1->coord[i] * vec_2->coord[i];
		i++;
	}
	return (result);
}

t_vec3	*add(t_vec3 *vec_1, t_vec3 *vec_2)
{
	t_vec3	*new_vec;
	int		i;

	new_vec = ft_calloc(1, sizeof(t_vec3));
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

t_vec3	*subtract(t_vec3 *vec_1, t_vec3 *vec_2)
{
	t_vec3	*new;
	t_vec3	*scaled_vec;

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

t_vec3	*cross(t_vec3 *vec_1, t_vec3 *vec_2)
{
	t_vec3		*vec;
	long double	tmp[3];
	int			i;

	i = 0;
	while (i < 3)
	{
		tmp[i] = vec_1->n_coord[(i + 1) % 3] * vec_2->n_coord[(i + 2) % 3] -
			vec_1->n_coord[(i + 2) % 3] * vec_2->n_coord[(i + 1) % 3];
		i++;
	}
	vec = create_vec(NULL, tmp);
	return (vec);
}

t_coord3	*offset(t_coord3 *p, t_vec3 *vec)
{
	long double val[COORD_SIZE];
	int i;

	if (!(p && vec))
		return (NULL);
	i = 0;
	while (i < COORD_SIZE)
	{
		val[i] = p[i] + vec->coord[i];
		i++;
	}
	return (create_coord(val[X], val[Y], val[Z]));
};
