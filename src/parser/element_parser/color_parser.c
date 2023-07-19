/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_parser.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 13:44:13 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/19 15:26:25 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mrt_macros.h>
#include <libft.h>
#include <stdio.h>

int	parse_color_code(char *color, int n_lower, int n_upper, t_line line_info)
{
	int		color_code;
	char	s_n_lower[4];
	char	s_n_upper[4];

	if (!is_valid_number(color))
		error((t_err){"Invalid color code representation", line_info.file, line_info.num, EXIT, 1});
	color_code = ft_atoi(color);
	snprintf(s_n_lower, 4, "%d", n_lower);
	snprintf(s_n_upper, 4, "%d", n_upper);
	if (!is_in_range_i(color_code, n_lower, n_upper))
		error((t_err){"Color code out of range: [0-255]", line_info.file, line_info.num, EXIT, 1});
	return (color_code);
}

void	parse_color(t_color *color, char *input, int n_lower, int n_upper, t_line line_info)
{
	char	**colors;
	int		i;
	int		color_code;
	int		parsed_color;

	parsed_color = 0;
	if (!color || !input)
		error((t_err){"NULL pointer (color)", __FILE__, __LINE__, EXIT, 1});
	colors = ft_split(input, ',');
	if (!colors)
		error((t_err){"Malloc error", __FILE__, __LINE__, EXIT, 1});
	else if (get_arr_size(colors) != 3)
		error((t_err){"Wrong color code separation/incomplete color code, required: R,G,B", line_info.file, line_info.num, EXIT, 1});
	i = 0;
	while (colors[i])
	{
		color_code = parse_color_code(colors[i], n_lower, n_upper, line_info);
		parsed_color |= color_code << (24 - (i * 8));
		i++;
	}
	parsed_color |= 0x000000FF;
	free_arr((void **) colors);
	*color = parsed_color;
}
