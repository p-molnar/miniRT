/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 11:55:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/19 15:22:26 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <libft.h>
#include <minirt.h>
#include <mrt_macros.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool	is_duplicate_el_type(enum e_scn_el_type_flags el_type, t_data *scn)
{
	t_list		*tmp;
	t_scn_el	*el;

	tmp = scn->all_scn_el;
	while (tmp)
	{
		el = tmp->content;
		if (is_in_range_i(el_type, F_AMB_LIGHT, F_TG_CAM))
		{
			if (el_type == el->type)
				return (true);
			else if (el_type == F_CAM && el->type == F_TG_CAM)
				return (true);
			else if (el_type == F_TG_CAM && el->type == F_CAM)
				return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

void	validate_scn_el_setup(t_data *scn)
{
	t_scn_el	*el;
	t_list		*tmp;
	long double	total_light_brightness;
	int			els;

	tmp = scn->all_scn_el;
	total_light_brightness = 0;
	els = 0;
	while (tmp)
	{
		el = tmp->content;
		total_light_brightness += el->intensity;
		els |= el->type;
		tmp = tmp->next;
	}
	if (!((els & F_CAM) || (els & F_TG_CAM)))
		error((t_err){"Required element: Camera", NULL, 0, EXIT, 1});
	if (scn && total_light_brightness < 0.05)
		warning(
			ft_strdup("Too dark scene: add lights, or increase brightness.")
			);
}

void	parse_data(t_data *scn, t_scn_el *el, char **input, t_line line_info)
{
	parse_type_identifier(el, input[0], line_info);
	if (is_duplicate_el_type(el->type, scn))
		error((t_err){"Duplicate element", line_info.file, line_info.num, EXIT, 1});
	if (el->type == F_AMB_LIGHT)
		parse_elements(el, input, AMB_LIGHT_FIELDS, line_info);
	else if (el->type == F_POINT_LIGHT)
		parse_elements(el, input, LIGHT_FIELDS, line_info);
	else if (el->type == F_DIR_LIGHT)
		parse_elements(el, input, DIR_LIGHT_FIELDS, line_info);
	else if (el->type == F_CAM)
		parse_elements(el, input, CAM_FIELDS, line_info);
	else if (el->type == F_TG_CAM)
		parse_elements(el, input, TG_CAM_FIELDS, line_info);
	else if (el->type == F_SPHERE)
		parse_elements(el, input, SPHERE_FIELDS, line_info);
	else if (el->type == F_PLANE)
		parse_elements(el, input, PLANE_FIELDS, line_info);
	else if (el->type == F_CYLINDER)
	{
		parse_elements(el, input, CYLINDER_FIELDS, line_info);
		add_cylinder_caps(el);
		populate_transformation_mx(el);
	}
}

void	parse_line(t_data *scn, t_line line)
{
	char		**el_data;
	t_scn_el	*el;
	t_list		*list_el;

	el_data = ft_split(line.content, ' ');
	el = ft_calloc(1, sizeof(t_scn_el));
	if (!el_data || !el)
		error((t_err){"Malloc error", __FILE__, __LINE__, EXIT, 1});
	parse_data(scn, el, el_data, line);
	list_el = ft_lstnew(el);
	if (!list_el)
		error((t_err){"Malloc error", __FILE__, __LINE__, EXIT, 1});
	ft_lstadd_back(&scn->all_scn_el, list_el);
	free_arr((void **)el_data);
}

void	parse_input(t_data *scn, int argc, char *argv[])
{
	int		fd;
	t_line	line;
	char	*tmp_line;

	if (argc != 2)
		error((t_err){"Expected arg count: 2", NULL, -1, EXIT, 1});
	fd = open_file(argv[1]);
	line.file = argv[1];
	line.content= get_next_line(fd);
	line.num = 1;
	while (line.content)
	{
		if (line.content[0] != '\n' && line.content[0] != '#')
		{
			tmp_line = line.content;
			line.content = ft_strtrim(tmp_line, "\n");
			if (!line.content)
				error((t_err){"Malloc error", __FILE__, __LINE__, EXIT, 1});
			free(tmp_line);
			parse_line(scn, line);
		}
		free(line.content);
		line.content = get_next_line(fd);
		line.num++;
	}
	if (line.content)
		free(line.content);
	validate_scn_el_setup(scn);
}
