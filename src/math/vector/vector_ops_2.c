/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_ops_2.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/28 14:48:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/02 11:41:03 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>

t_vec3	scale_vec(long double scaler, t_vec3 vec)
{
	t_coord3	tmp;
	int			i;

	i = 0;
	while (i < COORD_SIZE)
	{
		tmp.coord[i] = scaler * vec.dir.coord[i];
		i++;
	}
	return (coord_to_vec(tmp));
}

long double	dot(t_vec3 vec_1, t_vec3 vec_2)
{
	long double	result;
	int			i;

	result = 0;
	i = 0;
	while (i < COORD_SIZE)
	{
		result += vec_1.dir.coord[i] * vec_2.dir.coord[i];
		i++;
	}
	return (result);
}

t_vec3	add_vec(t_vec3 vec_1, t_vec3 vec_2)
{
	t_coord3	tmp;
	int			i;

	i = 0;
	while (i < COORD_SIZE)
	{
		tmp.coord[i] = vec_1.dir.coord[i] + vec_2.dir.coord[i];
		i++;
	}
	return (coord_to_vec(tmp));
}

t_vec3	subtract_vec(t_vec3 vec_1, t_vec3 vec_2)
{
	t_vec3	return_vec;

	return_vec = add_vec(vec_1, scale_vec(-1, vec_2));
	return_vec.len = get_vec_len(return_vec);
	return (return_vec);
}

t_vec3	cross(t_vec3 vec_1, t_vec3 vec_2)
{
	t_vec3		normal[2];
	t_coord3	return_vec;
	int			i;

	normalize_vec(&vec_1);
	normalize_vec(&vec_2);
	normal[0] = vec_1;
	normal[1] = vec_2;
	i = 0;
	while (i < COORD_SIZE)
	{
		return_vec.coord[i] = normal[0].dir.coord[(i + 1) % 3]
			* normal[1].dir.coord[(i + 2) % 3]
			- normal[0].dir.coord[(i + 2) % 3]
			* normal[1].dir.coord[(i + 1) % 3];
		i++;
	}
	return (coord_to_vec(return_vec));
}
