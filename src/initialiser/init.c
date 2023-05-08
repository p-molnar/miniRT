/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 10:46:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/08 20:27:41 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void	init_scene(t_data *scn)
{
	ft_memset(scn, 0, sizeof(t_data));
}

void	create_projection_plane(t_data *d)
{
	long double	fov_rad;
	t_scn_el	**cam;

	cam = get_scn_els(d->scn_el, CAM);
	if (!cam)
		error(ft_strdup("No camera found\n"), EXIT, 1);
	fov_rad = deg_to_rad(cam[0]->fov / 2.0);
	d->viewport[WIDTH] = 1;
	d->viewport[HEIGHT] = 1;
	d->viewport[DEPTH] = 0.5 / tan(fov_rad);
	free(cam);
}

int	is_cam_rotated(t_vec *n_vec)
{
	int	i;

	i = 0;
	while (i < COORD_SIZE && n_vec)
	{
		if (n_vec->coord[i] != 0)
			return (1);
		i++;
	}
	return (0);
}

void	set_up_rotation_mx(t_data *data)
{
	const long double	def_cam_orientation[COORD_SIZE] = {0, 0, 1};
	t_vec				*rot_axis;
	long double			r_angle;

	t_vec	*cam_orientation_vec = create_vec(NULL, (long double *) def_cam_orientation);
	if (is_cam_rotated(data->cam->n_vec))
	{
		normalize_vec(data->cam->n_vec);
		r_angle = rad_to_deg(acos(dot(cam_orientation_vec, data->cam->n_vec)));
		rot_axis = cross(cam_orientation_vec, data->cam->n_vec);
	}
	else
	{
		r_angle = rad_to_deg(0);
		rot_axis = cross(cam_orientation_vec, cam_orientation_vec);
	}
	printf("angle: %Lf\n", r_angle);
	printf("rotation axis: %Lf, %Lf, %Lf\n", rot_axis->coord[0], rot_axis->coord[1], rot_axis->coord[2]);
	data->rotation_mx = get_rotation_mx(r_angle, rot_axis);
	free(cam_orientation_vec);
	free(rot_axis);
}

void	set_up_vars(t_data *data)
{
	t_list		*ptr;
	t_scn_el	*obj;
	t_scn_el	**cam;

	ptr = data->scn_el;
	while (ptr)
	{
		obj = ptr->content;
		obj->radius = obj->diameter / 2;
		ptr = ptr->next;
	}
	cam = get_scn_els(data->scn_el, CAM);
	if (cam)
		data->cam = cam[0];
	set_up_rotation_mx(data);
}