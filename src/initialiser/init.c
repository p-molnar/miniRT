/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 10:46:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/09 19:29:52 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <stdio.h>
#include <stdlib.h>

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
	el->translation = get_translation_mx(el->pos.x, el->pos.y, el->pos.z);
	el->inv_translation = get_inverse_mx(el->translation);
}

void	populate_rotation_mx(t_data *d, t_scn_el *el)
{
	long double		agl_r;
	t_vec3			*pivot_ax;
	t_mx			*pivot_mx;

	if (is_identical_coord((t_coord3) {{0, 0, 0}}, el->n_vec->dir))
		el->n_vec->dir.z = 1;
	agl_r = get_agl_between(d->dft_world_orientation, el->n_vec);
	printf("agl_r: %Lf\n", agl_r);
	pivot_ax = cross(d->dft_world_orientation, el->n_vec);
	normalize(pivot_ax);
	pivot_mx  = coord_to_mx(&pivot_ax->dir, 3, 1);
	expand_mx(pivot_mx, 4, 1, 1);
	printf("pivot_mx\n");
	print_mx(pivot_mx);
	el->rotation = get_rotation_mx(pivot_mx, agl_r);
	el->inv_rotation = get_inverse_mx(el->rotation);
	print_mx(el->inv_rotation);
	free_mx(pivot_mx);
}

void	populate_transformation_mx(t_data *d, t_scn_el *el)
{
	populate_translation_mx(el);
	populate_rotation_mx(d, el);
}

void	set_up_camera(t_data *d)
{
	t_vec3		*right_vec;
	t_vec3		*fw_vec;
	t_vec3		*up_vec;
	t_scn_el	*cam;

	cam = *d->scn_els[CAM];
	if (cam->type == F_CAM)
		fw_vec = coord_to_vec(cam->n_vec->dir);
	else
	{
		fw_vec = create_dir_vec(cam->pos, cam->target);
		normalize(fw_vec);
	}
	if (fw_vec->dir.x == 0 && fw_vec->dir.y == 0 && fw_vec->dir.z == 0)
	{
		fw_vec->dir.z = 1;
		fw_vec->len = 1;
	}
	else if ((fw_vec->dir.x == 0 && fw_vec->dir.z == 0) && (fw_vec->dir.y ==
				-1 || fw_vec->dir.y == 1))
	{
		d->dft_up_vec->dir.y = 0;
		d->dft_up_vec->dir.z = 1;
		fw_vec->len = 1;
	}
	right_vec = cross(d->dft_up_vec, fw_vec);
	normalize(right_vec);
	up_vec = cross(fw_vec, right_vec);
	normalize(up_vec);
	d->ctw_mx = malloc(sizeof(t_mx));
	d->ctw_mx->r = 4;
	d->ctw_mx->c = 4;
	d->ctw_mx->m = ft_calloc(16, sizeof(long double));
	d->ctw_mx->m[0] = right_vec->dir.x;
	d->ctw_mx->m[1] = up_vec->dir.x;
	d->ctw_mx->m[2] = fw_vec->dir.x;
	d->ctw_mx->m[3] = cam->pos.x;
	d->ctw_mx->m[4] = right_vec->dir.y;
	d->ctw_mx->m[5] = up_vec->dir.y;
	d->ctw_mx->m[6] = fw_vec->dir.y;
	d->ctw_mx->m[7] = cam->pos.y;
	d->ctw_mx->m[8] = right_vec->dir.z;
	d->ctw_mx->m[9] = up_vec->dir.z;
	d->ctw_mx->m[10] = fw_vec->dir.z;
	d->ctw_mx->m[11] = cam->pos.z;
	d->ctw_mx->m[15] = 1;
	free(fw_vec);
	free(up_vec);
	free(right_vec);
	print_mx(d->ctw_mx);
}
