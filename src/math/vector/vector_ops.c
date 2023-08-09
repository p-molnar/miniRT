/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_ops.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/24 15:01:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/09 18:12:43 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>

t_vec3	create_vec(t_coord x, t_coord y, t_coord z)
{
	t_vec3	vec;

	vec.dir.x = x;
	vec.dir.y = y;
	vec.dir.z = z;
	vec.len = get_vec_len(vec);
	return (vec);
}

t_vec3	create_dir_vec(t_coord3 init_point, t_coord3 term_point)
{
	t_vec3		dir;

	dir = coord_to_vec(subtract_coord(term_point, init_point));
	return (dir);
}

long double	get_vec_len(t_vec3 vec)
{
	long double	sum_of_sqrs;
	int			i;

	sum_of_sqrs = 0;
	i = 0;
	while (i < COORD_SIZE)
	{
		sum_of_sqrs += pow(vec.dir.coord[i], 2);
		i++;
	}
	return (sqrt(sum_of_sqrs));
}

void	normalize_vec(t_vec3 *vec)
{
	int	i;

	if (!vec)
		return ;
	i = 0;
	while (i < COORD_SIZE)
	{
		if (vec->len > 0)
			vec->dir.coord[i] = vec->dir.coord[i] / vec->len;
		else
			vec->dir.coord[i] = 0;
		i++;
	}
	vec->len = 1;
}
