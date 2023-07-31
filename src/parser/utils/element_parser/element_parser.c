/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   element_parser.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 09:27:54 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/31 00:52:52 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mrt_data_struct.h>
#include <mrt_error.h>
#include <mrt_macros.h>
#include <stdio.h>

void	parse_type_identifier(t_scn_el *el, char *line, t_line line_info)
{
	int	el_type;
	int	str_len;

	str_len = ft_strlen(line) + 1;
	el_type = F_TYPE_UNDEF;
	if (ft_strncmp("A", line, str_len) == 0)
		el_type = F_AMB_LIGHT;
	else if (ft_strncmp("L", line, str_len) == 0)
		el_type = F_POINT_LIGHT;
	else if (ft_strncmp("DL", line, str_len) == 0)
		el_type = F_DIR_LIGHT;
	else if (ft_strncmp("C", line, str_len) == 0)
		el_type = F_CAM;
	else if (ft_strncmp("TC", line, str_len) == 0)
		el_type = F_TG_CAM;
	else if (ft_strncmp("sp", line, str_len) == 0)
		el_type = F_SPHERE;
	else if (ft_strncmp("pl", line, str_len) == 0)
		el_type = F_PLANE;
	else if (ft_strncmp("cy", line, str_len) == 0)
		el_type = F_CYLINDER;
	else
		error((t_err){WRONG_EL, line_info.file, line_info.num, EXIT, 1});
	el->type = el_type;
}

void	populate_data_fields(t_scn_el *el, char **input, unsigned int field,
		t_line line_info)
{
	int	col;

	col = 1;
	if (field & F_COORD)
		parse_coordinates(&el->pos, input[col++], line_info);
	if (field & F_TG_COORD)
		parse_coordinates(&el->target, input[col++], line_info);
	if (field & F_N_VEC)
		parse_norm_vec(&el->n_vec, input[col++], line_info);
	if (field & F_DMETER)
		parse_float(&el->diameter, input[col++], line_info);
	if (field & F_HEIGHT)
		parse_float(&el->height, input[col++], line_info);
	if (field & F_FOV)
		parse_range(&el->fov, input[col++], (t_range){0, 180}, line_info);
	if (field & F_INTENSITY)
		parse_range(&el->intensity, input[col++], (t_range){0, 1}, line_info);
	if (field & F_COLOR)
		parse_color(&el->color, input[col++], (t_range){0, 255}, line_info);
	if (field & F_SPECULAR)
		parse_range(&el->spec_coeff, input[col++], (t_range){-1, 999},
			line_info);
	if (field & F_REFLECTION)
		parse_range(&el->refl_coeff, input[col++], (t_range){0, 1}, line_info);
}