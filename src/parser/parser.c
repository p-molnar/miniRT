/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 11:55:08 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/01 13:32:46 by pmolnar       ########   odam.nl         */
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
		if (is_in_range_i(el_type, AMB_LIGHT, CAM) && tmp_el_type == el_type)
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
	if (!(els & (1 << CAM)))
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
		parse_elements(el, input, F_INTENSITY | F_COLOR);
	else if (el->type == LIGHT)
		parse_elements(el, input, F_COORD | F_INTENSITY | F_COLOR);
	else if (el->type == DIR_LIGHT)
		parse_elements(el, input, F_N_VEC | F_INTENSITY);
	else if (el->type == CAM)
		parse_elements(el, input, F_COORD | F_N_VEC | F_FOV);
	else if (el->type == SPHERE)
		parse_elements(el, input, F_COORD | F_DMETER | F_COLOR);
	else if (el->type == PLANE)
		parse_elements(el, input, F_COORD | F_N_VEC | F_COLOR);
	else if (el->type == CYLYNDER)
		parse_elements(el, input,
			F_COORD | F_N_VEC | F_DMETER | F_HEIGHT | F_COLOR);
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
