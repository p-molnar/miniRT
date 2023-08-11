/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_validator.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 23:20:51 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/11 10:00:37 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>
#include <stdlib.h>

static bool	is_cam_inside_sphere(t_scn_el cam, t_scn_el el)
{
	t_coord3	diff;

	diff = subtract_coord(el.pos, cam.pos);
	return (pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2) < pow(el.diameter
			/ 2, 2));
}

static bool	is_cam_in_cylinder(t_scn_el cam, t_scn_el el)
{
	t_coord3	diff;
	t_mx		transformed_pos;

	transformed_pos = coord_to_mx(cam.pos, 4, 1, 1);
	transformed_pos = multiply_mx(el.inv_rotation, transformed_pos);
	transformed_pos = multiply_mx(el.inv_translation, transformed_pos);
	diff = create_coord(transformed_pos.m[X], transformed_pos.m[Y],
			transformed_pos.m[Z]);
	return ((diff.z > el.cap[0].pos.z && diff.z < el.cap[1].pos.z)
		&& (pow(diff.x, 2) + pow(diff.y, 2) < pow(el.diameter / 2, 2)));
}

static bool	is_cam_inside_obj(t_data data)
{
	t_scn_el	**cam;
	t_scn_el	**el;
	int			i;
	int			is_inside;
	t_coord3	offset_cam_position;

	cam = get_scn_els(data.scn_el_list, F_CAM);
	el = get_scn_els(data.scn_el_list, F_SPHERE | F_PLANE | F_CYLINDER);
	normalize_vec(&cam[0]->orientation);
	offset_cam_position = offset_pt(cam[0]->pos, cam[0]->orientation);
	cam[0]->pos = offset_cam_position;
	i = 0;
	is_inside = 0;
	while (el && el[i] && !is_inside)
	{
		if (el[i]->type == F_SPHERE && is_cam_inside_sphere(*cam[0], *el[i]))
			is_inside = 1;
		else if (el[i]->type == F_CYLINDER && is_cam_in_cylinder(*cam[0],
				*el[i]))
			is_inside = 1;
		i++;
	}
	free(cam);
	free(el);
	return (is_inside == 1);
}

void	validate_scn_el_setup(t_data *data, t_line line_info)
{
	t_scn_el	*el;
	t_list		*tmp;
	int			els;

	tmp = data->scn_el_list;
	els = 0;
	while (tmp)
	{
		el = tmp->content;
		els |= el->type;
		tmp = tmp->next;
	}
	if (!((els & F_CAM) || (els & F_TG_CAM)))
		error((t_err){CAM_REQUIRED, NULL, 0, EXIT, 1});
	if (is_cam_inside_obj(*data))
		error((t_err){CAM_INSIDE_OBJ, line_info.file, -1, EXIT, 1});
}

void	validate_for_duplicate_el(enum e_scn_el_type_flags el_type, t_data *scn,
		t_line line_info)
{
	bool		duplicate_found;
	t_list		*tmp;
	t_scn_el	*curr_el;

	duplicate_found = false;
	tmp = scn->scn_el_list;
	while (tmp && !duplicate_found)
	{
		curr_el = tmp->content;
		if (is_in_range_f(el_type, F_AMB_LIGHT, F_POINT_LIGHT, "[)"))
		{
			if (curr_el->type == el_type)
				duplicate_found = 1;
			else if ((el_type == F_TG_CAM && curr_el->type == F_CAM) || 
				(el_type == F_CAM && curr_el->type == F_TG_CAM))
				duplicate_found = 1;
		}
		tmp = tmp->next;
	}
	if (duplicate_found)
		error((t_err){DUPLICATE_EL, line_info.file, line_info.num, EXIT, 1});
}
