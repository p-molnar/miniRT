/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   double_parser.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 12:37:52 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/19 11:06:25 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <mrt_macros.h>
#include <libft.h>
#include <stdio.h>

void	parse_double(double *f, char *input)
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

void	parse_range(double *f, char *input, double n_lower, double n_upper)
{
	char	s_n_lower[4];
	char	s_n_upper[4];

	if (!f || !input)
		error(ft_strdup("NULL Pointer error: __FILE__: __LINE__"), EXIT, 1);
	if (!is_valid_number(input))
		error(strconcat(2, "Invalid number: ", input), EXIT, 1);
	*f = ft_atof(input);
	snprintf(s_n_lower, 4, "%f", n_lower);
	snprintf(s_n_upper, 4, "%f", n_upper);
	if (!is_in_range_f(*f, n_lower, n_upper))
		error(strconcat(6, "Number out of range [", s_n_lower,
				", ", s_n_upper, "]: ", input), EXIT, 1);
}
