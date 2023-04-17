/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   float_parser.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 12:37:52 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/17 13:51:28 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mrt_macros.h>
#include <libft.h>
#include <stdio.h>

void	parse_float(float *f, char *input)
{
	if (!f || !input)
		error(ft_strdup("NULL Pointer error: __FILE__: __LINE__"), EXIT, 1);
	if (!is_valid_number(input))
		error(strconcat(2, "Invalid number: ", input), EXIT, 1);
	*f = ft_atof(input);
	if (f < 0)
		error(strconcat(2, "Number out of range [0.0, ∞): ", input),
			EXIT, 1);
}

void	parse_range(float *f, char *input, float n_lower, float n_upper)
{
	char	str_n_lower[4];
	char	str_n_upper[4];

	if (!f || !input)
		error(ft_strdup("NULL Pointer error: __FILE__: __LINE__"), EXIT, 1);
	if (!is_valid_number(input))
		error(strconcat(2, "Invalid number: ", input), EXIT, 1);
	*f = ft_atof(input);
	snprintf(str_n_lower, 4, "%f", n_lower);
	snprintf(str_n_upper, 4, "%f", n_upper);
	if (f < 0)
		error(strconcat(6, "Number out of range: ", "[", str_n_lower, ", ",
				str_n_upper, "]"), EXIT, 1);
}
