/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_parser.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 13:44:13 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/02 11:26:27 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt.h>
#include <mrt_error.h>
#include <mrt_macros.h>
#include <stdio.h>

int	parse_color_code(char *color, int rgb_min, int rgb_max, t_line line_info)
{
	int	rgb_val;

	if (!is_valid_number(color))
		error((t_err){INVALID_NUM, line_info.file, line_info.num, EXIT, 1});
	rgb_val = ft_atoi(color);
	if (!is_in_range_f(rgb_val, rgb_min, rgb_max, "[]"))
		error((t_err){OUT_OF_RANGE, line_info.file, line_info.num, EXIT, 1});
	return (rgb_val);
}

void	parse_color(t_color *color, char *input, t_range range,
		t_line line_info)
{
	char	**colors;
	int		i;
	t_color	parsed_color;

	if (!color || !input)
		error((t_err){NULL_PTR, __FILE__, __LINE__, EXIT, 1});
	colors = ft_split(input, ',');
	if (!colors)
		error((t_err){strerror(errno), __FILE__, __LINE__, EXIT, 1});
	else if (get_arr_size(colors) != 3)
		error((t_err){WRONG_SEP, line_info.file, line_info.num, EXIT, 1});
	i = 0;
	parsed_color.r = parse_color_code(colors[0], range.min, range.max,
			line_info);
	parsed_color.g = parse_color_code(colors[1], range.min, range.max,
			line_info);
	parsed_color.b = parse_color_code(colors[2], range.min, range.max,
			line_info);
	i++;
	parsed_color.a = 255;
	free_arr((void **)colors);
	*color = parsed_color;
}
