/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 11:55:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/26 11:45:13 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt.h>
#include <mrt_macros.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>

int	is_duplicate_el_type(int el_type, t_data *scn)
{
	t_list	*tmp;
	int		tmp_el_type;

	tmp = scn->scn_el;
	while (tmp)
	{
		tmp_el_type = ((t_scn_el *)tmp->content)->type;
		if (is_in_range_i(el_type, AMB_LIGHT, TG_CAM) && tmp_el_type == el_type)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	validate_scn_el_setup(t_data *scn)
{
	t_scn_el		*el;
	t_list			*tmp;
	long double		total_light_brightness;
	int				els;

	tmp = scn->scn_el;
	total_light_brightness = 0;
	els = 0;
	while (tmp)
	{
		el = tmp->content;
		total_light_brightness += el->intensity;
		els |= 1 << el->type;
		tmp = tmp->next;
	}
	if (!((els & F_CAM) || (els & F_TG_CAM)))
		error(ft_strdup("Add a camera to the scene."), EXIT, 1);
	if (scn && total_light_brightness < 0.05)
		warning(ft_strdup("Scene too dark, consider increasing brightness."));
}

void	parse_data(t_data *scn, t_scn_el *el, char **input)
{
	const char	*type[8] = {"Undefined", "Ambient light", "Light", "Dir. Light",
		"Camera", "Sphere", "Plane", "Cylinder"}; // rewrite

	parse_type_identifier(el, input[0]);
	if (is_duplicate_el_type(el->type, scn))
		error(strconcat(2, "Duplicate element type: ", type[el->type]),
			EXIT, 1);
	if (el->type == AMB_LIGHT)
		parse_elements(el, input, F_AMB_LIGHT);
	else if (el->type == POINT_LIGHT)
		parse_elements(el, input, F_LIGHT);
	else if (el->type == DIR_LIGHT)
		parse_elements(el, input, F_DIR_LIGHT);
	else if (el->type == CAM)
		parse_elements(el, input, F_CAM);
	else if (el->type == TG_CAM)
		parse_elements(el, input, F_TG_CAM);
	else if (el->type == SPHERE)
		parse_elements(el, input, F_SPHERE);
	else if (el->type == PLANE)
		parse_elements(el, input, F_PLANE);
	else if (el->type == CYLINDER)
		parse_elements(el, input, F_CYLINDER);
}

void	parse_line(t_data *scn, char *line)
{
	char		**el_info;
	t_scn_el	*el;
	t_list		*list_el;

	el_info = ft_split(line, ' ');
	el = ft_calloc(1, sizeof(t_scn_el));
	if (!el_info || !el)
		error(strconcat(4, "Malloc error: ", __FILE__, ":", ft_itoa(__LINE__)),
			EXIT, 1);
	parse_data(scn, el, el_info);
	list_el = ft_lstnew(el);
	if (!list_el)
		error(strconcat(4, "Malloc error: ", __FILE__, ":", ft_itoa(__LINE__)),
			EXIT, 1);
	ft_lstadd_back(&scn->scn_el, list_el);
	free_arr((void **) el_info);
}

void	parse_scene(t_data *scn, int argc, char *argv[])
{
	int		fd;
	char	*line;
	char	*tmp;

	if (argc != 2)
		error(ft_strdup("Invalid argument count"), EXIT, 1);
	fd = open_file(argv[1]);
	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n')
		{
			tmp = line;
			line = ft_strtrim(line, "\n");
			if (!line)
				error(strconcat(4, "Malloc error: ", __FILE__, ": ",
						ft_itoa(__LINE__)), EXIT, 1);
			free(tmp);
			if (*line != '#')
				parse_line(scn, line);
		}
		free(line);
		line = get_next_line(fd);
	}
	validate_scn_el_setup(scn);
}
