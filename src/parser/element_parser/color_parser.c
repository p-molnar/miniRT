/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_parser.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 13:44:13 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/12 11:49:12 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mrt_macros.h>
#include <libft.h>
#include <stdio.h>

int	parse_color_code(char *color, int n_lower, int n_upper)
{
	int		color_code;
	char	s_n_lower[4];
	char	s_n_upper[4];

	if (!is_valid_number(color))
		error(strconcat(2, "Invalid number: ", color), EXIT, 1);
	color_code = ft_atoi(color);
	snprintf(s_n_lower, 4, "%d", n_lower);
	snprintf(s_n_upper, 4, "%d", n_upper);
	if (!is_in_range_i(color_code, n_lower, n_upper))
		error(strconcat(6, "Number out of range [", s_n_lower,
				", ", s_n_upper, "]: ", color), EXIT, 1);
	return (color_code);
}

void	parse_color(t_color *color, char *input, int n_lower, int n_upper)
{
	char	**colors;
	int		i;
	t_color	color_code;
	t_color	parsed_color;

	parsed_color.color = 0;
	if (!color || !input)
		error(ft_strdup("NULL Pointer error"), EXIT, 1);
	colors = ft_split(input, ',');
	if (!colors)
		error(strconcat(4, "Malloc error: ", __FILE__, ":", ft_itoa(__LINE__)),
			EXIT, 1);
	else if (get_arr_size(colors) != 3)
		error(ft_strdup("Required color components: R, G, B"), EXIT, 1);
	i = 0;
	while (colors[i])
	{
		color_code.color = parse_color_code(colors[i], n_lower, n_upper);
		parsed_color.color |= color_code.color << (24 - (i * 8));
		i++;
	}
	parsed_color.color |= 0x000000FF;
	free_arr((void **) colors);
	*color = parsed_color;
}
