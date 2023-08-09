/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 11:55:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/09 18:18:52 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>

static void	populate_column_data(t_scn_el *el, char **input,
		t_line line_info)
{
	if (el->type == F_AMB_LIGHT)
		populate_data_fields(el, input, AMB_LIGHT_FIELDS, line_info);
	else if (el->type == F_POINT_LIGHT)
		populate_data_fields(el, input, LIGHT_FIELDS, line_info);
	else if (el->type == F_DIR_LIGHT)
		populate_data_fields(el, input, DIR_LIGHT_FIELDS, line_info);
	else if (el->type == F_CAM)
		populate_data_fields(el, input, CAM_FIELDS, line_info);
	else if (el->type == F_TG_CAM)
		populate_data_fields(el, input, TG_CAM_FIELDS, line_info);
	else if (el->type == F_SPHERE)
		populate_data_fields(el, input, SPHERE_FIELDS, line_info);
	else if (el->type == F_PLANE)
		populate_data_fields(el, input, PLANE_FIELDS, line_info);
	else if (el->type == F_CYLINDER)
	{
		populate_data_fields(el, input, CYLINDER_FIELDS, line_info);
		add_cylinder_caps(el);
		populate_transformation_mx(el);
	}
}

static void	parse_column_data(t_data *data, t_scn_el *el, char **input,
		t_line line_info)
{
	parse_type_identifier(el, input[0], line_info);
	validate_for_duplicate_el(el->type, data, line_info);
	validate_line_formatting(*el, input, line_info);
	populate_column_data(el, input, line_info);
	populate_derived_fields(el);
}

static void	parse_line(t_data *scn, t_line *line)
{
	char		**line_content;
	t_scn_el	*element_info;
	t_list		*list_el;
	char		*tmp_line;

	tmp_line = line->content;
	line->content = ft_strtrim(tmp_line, "\n");
	free(tmp_line);
	if (!line->content)
		error((t_err){strerror(errno), __FILE__, __LINE__, EXIT, 1});
	line_content = ft_split(line->content, ' ');
	element_info = ft_calloc(1, sizeof(t_scn_el));
	if (!line_content || !element_info)
		error((t_err){strerror(errno), __FILE__, __LINE__, EXIT, 1});
	parse_column_data(scn, element_info, line_content, *line);
	list_el = ft_lstnew(element_info);
	if (!list_el)
		error((t_err){strerror(errno), __FILE__, __LINE__, EXIT, 1});
	ft_lstadd_back(&scn->scn_el_list, list_el);
	free_arr((void **)line_content);
}

void	parse_input(t_data *scn, int argc, char *argv[])
{
	int		fd;
	t_line	line;

	if (argc != 2)
		error((t_err){REQUIRED_ARGC, NULL, -1, EXIT, 1});
	fd = open_file(argv[1]);
	line.file = argv[1];
	line.content = get_next_line(fd);
	line.num = 1;
	while (line.content)
	{
		if (line.content[0] != '\n' && line.content[0] != '#')
			parse_line(scn, &line);
		free(line.content);
		line.content = get_next_line(fd);
		line.num++;
	}
	validate_scn_el_setup(scn);
}
