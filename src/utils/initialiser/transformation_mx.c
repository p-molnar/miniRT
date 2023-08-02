/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transformation_mx.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/21 12:49:21 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/02 11:41:03 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdio.h>

bool	is_identical_coord(t_coord3 c1, t_coord3 c2)
{
	int	i;

	i = 0;
	while (i < COORD_SIZE)
	{
		if (c1.coord[i] != c2.coord[i])
			return (false);
		i++;
	}
	return (true);
}

void	populate_translation_mx(t_scn_el *el)
{
	t_mx	trans_mx;
	t_mx	inv_trans_mx;

	trans_mx = get_translation_mx(el->pos.x, el->pos.y, el->pos.z);
	inv_trans_mx = get_inverse_mx(trans_mx);
	ft_memcpy(&el->translation, &trans_mx, sizeof(t_mx));
	ft_memcpy(&el->inv_translation, &inv_trans_mx, sizeof(t_mx));
}

void	populate_rotation_mx(t_scn_el *el)
{
	long double	agl_r;
	t_vec3		pivot_ax;
	t_mx		pivot_mx;
	t_mx		rot_mx;
	t_mx		inv_rot_mx;

	if (is_identical_coord((t_coord3){{0, 0, 0}}, el->n_vec.dir))
		el->n_vec.dir.z = 1;
	agl_r = get_agl_between(create_vec(0, 0, 1), el->n_vec);
	printf("agl_r: %Lf\n", agl_r);
	pivot_ax = cross(create_vec(0, 0, 1), el->n_vec);
	normalize_vec(&pivot_ax);
	pivot_mx = coord_to_mx(pivot_ax.dir, 4, 1, 1);
	rot_mx = get_rotation_mx(pivot_mx, agl_r);
	inv_rot_mx = get_inverse_mx(rot_mx);
	ft_memcpy(&el->rotation, &rot_mx, sizeof(t_mx));
	ft_memcpy(&el->inv_rotation, &inv_rot_mx, sizeof(t_mx));
	printf("rotation_mx\n");
	print_mx(&el->rotation);
	printf("inverse_rotation mx\n");
	print_mx(&el->inv_rotation);
}

void	populate_transformation_mx(t_scn_el *el)
{
	populate_translation_mx(el);
	populate_rotation_mx(el);
}
