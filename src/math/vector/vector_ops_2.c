/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_ops_2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/28 14:48:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/09 23:31:13 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>

t_vec3	*scale(long double scaler, t_vec3 *vec)
{
	t_coord3	tmp;
	int			i;

	if (!vec)
		return (NULL);
	i = 0;
	while (i < COORD_SIZE)
	{
		tmp.coord[i] = scaler * vec->dir.coord[i];
		i++;
	}
	return (coord_to_vec(tmp));
}

long double	dot(t_vec3 *vec_1, t_vec3 *vec_2)
{
	long double	result;
	int			i;

	if (!vec_1 || !vec_2)
		return (0);
	result = 0;
	i = 0;
	while (i < COORD_SIZE)
	{
		result += vec_1->dir.coord[i] * vec_2->dir.coord[i];
		i++;
	}
	return (result);
}

t_vec3	*add(t_vec3 *vec_1, t_vec3 *vec_2)
{
	t_coord3	tmp;
	int		i;

	if (!vec_1 || !vec_2)
		return (NULL);
	i = 0;
	while (i < COORD_SIZE)
	{
		tmp.coord[i] = vec_1->dir.coord[i] + vec_2->dir.coord[i];
		i++;
	}
	return (coord_to_vec(tmp));
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
	new->len = get_vec_len(new);
	free(scaled_vec);
	return (new);
}

t_vec3	*cross(t_vec3 *vec_1, t_vec3 *vec_2)
{
	t_vec3		*vec;
	t_vec3		*normal[2];
	t_coord3	tmp;
	int			i;

	if (!vec_1 || !vec_2)
		return (NULL);
	normal[0] = get_normal_vec(vec_1);
	normal[1] = get_normal_vec(vec_2);
	i = 0;
	while (i < COORD_SIZE)
	{
		tmp.coord[i] = normal[0]->dir.coord[(i + 1) % 3]
			* normal[1]->dir.coord[(i + 2) % 3] -
			normal[0]->dir.coord[(i + 2) % 3] * normal[1]->dir.coord[(i + 1)
				% 3];
		i++;
	}
	vec = coord_to_vec(tmp);
	free(normal[0]);
	free(normal[1]);
	return (vec);
}

t_coord3	*offset(t_coord3 *p, t_vec3 *vec)
{
	t_coord3	new_point;
	t_coord3	*offset_vec;
	int i;

	if (!(p && vec))
		return (NULL);
	i = 0;
	while (i < COORD_SIZE)
	{
		new_point.coord[i] = p->coord[i] + vec->dir.coord[i];
		i++;
	}
	offset_vec = create_coord(new_point.x, new_point.y, new_point.z);
	return (offset_vec);
};
