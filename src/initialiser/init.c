/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/08 10:46:11 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/24 23:15:18 by pmolnar       ########   odam.nl         */
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

int	is_cam_rotated(t_vec3 *n_vec)
{
	int	i;

	i = 0;
	while (i < COORD_SIZE && n_vec)
	{
		if (n_vec->dir[i] != 0)
			return (1);
		i++;
	}
	return (0);
}

void	set_up_rotation_mx(t_data *data)
{
	t_coord3	*default_orientation;
	t_vec3				*rot_axis;
	long double			r_angle;

	default_orientation = create_coord(0, 0, 1);
	t_vec3	*cam_orientation_vec = create_vec(NULL, default_orientation);
	if (is_cam_rotated(data->cam->n_vec))
	{
		data->cam->n_vec = get_normal_vec(data->cam->n_vec);
		r_angle = rad_to_deg(acos(dot(cam_orientation_vec, data->cam->n_vec)));
		rot_axis = cross(cam_orientation_vec, data->cam->n_vec);
	}
	else
	{
		r_angle = rad_to_deg(0);
		rot_axis = cross(cam_orientation_vec, cam_orientation_vec);
	}
	// printf("angle: %Lf\n", r_angle);
	// printf("rotation axis: %Lf, %Lf, %Lf\n", rot_axis->dir[0], rot_axis->dir[1], rot_axis->dir[2]);
	data->rot_axis = rot_axis;
	data->rot_angle = r_angle;
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