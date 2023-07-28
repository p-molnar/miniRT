/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_validator.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/25 23:20:51 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/28 14:15:06 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <minirt.h>
#include <mrt_error.h>
#include <stdlib.h>

static bool	is_cam_inside_sphere(t_scn_el cam, t_scn_el el)
{
	t_coord3	diff;

	diff = coord_subtract(el.pos, cam.pos);
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

	cam = get_scn_els(data.all_scn_el, F_CAM);
	el = get_scn_els(data.all_scn_el, F_SPHERE | F_PLANE | F_CYLINDER);
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

void	validate_scn_el_setup(t_data *data)
{
	t_scn_el	*el;
	t_list		*tmp;
	int			els;

	tmp = data->all_scn_el;
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
		error((t_err){CAM_INSIDE_OBJ, NULL, 0, EXIT, 1});
}

void	validate_for_duplicate_el(enum e_scn_el_type_flags el_type, t_data *scn,
		t_line line_info)
{
	bool		dupl_found;
	t_list		*tmp;
	t_scn_el	*el;

	dupl_found = false;
	tmp = scn->all_scn_el;
	while (tmp && !dupl_found)
	{
		el = tmp->content;
		if (is_in_range_i(el_type, F_AMB_LIGHT, F_TG_CAM))
		{
			if (el_type == el->type)
				dupl_found = 1;
			else if (el_type == F_CAM && el->type == F_TG_CAM)
				dupl_found = 1;
			else if (el_type == F_TG_CAM && el->type == F_CAM)
				dupl_found = 1;
		}
		tmp = tmp->next;
	}
	if (dupl_found)
		error((t_err){DUPLICATE_EL, line_info.file, line_info.num, EXIT, 1});
}