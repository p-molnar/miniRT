/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_parser.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 13:44:13 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/17 18:24:39 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mrt_macros.h>
#include <libft.h>
#include <stdio.h>

int	parse_color_code(char *color, int n_lower, int n_upper)
{
	int		color_code;
	char	str_n_lower[4];
	char	str_n_upper[4];

	if (!is_valid_number(color))
		error(strconcat(2, "Invalid number: ", color), EXIT, 1);
	color_code = ft_atoi(color);
	snprintf(str_n_lower, 4, "%d", n_lower);
	snprintf(str_n_upper, 4, "%d", n_upper);
	if (!is_in_range_i(color_code, n_lower, n_upper))
		error(strconcat(6, "Number out of range: ", "[", str_n_lower, ", ",
				str_n_upper, "]"), EXIT, 1);
	return (color_code);
}

void	parse_color(unsigned int *color, char *input, int n_lower, int n_upper)
{
	char	**colors;
	int		i;
	int		color_code;

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
		color_code = parse_color_code(colors[i], n_lower, n_upper);
		color[i] = color_code;
		i++;
	}
	free_arr(colors);
}
