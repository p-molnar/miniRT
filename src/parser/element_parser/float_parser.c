/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   float_parser.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/17 12:37:52 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/19 14:40:28 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt.h>
#include <mrt_macros.h>
#include <stdio.h>

void	parse_float(long double *f, char *input)
{
	if (!f || !input)
		error((t_err){"NULL pointer", __FILE__, __LINE__, EXIT, 1});
	if (!is_valid_number(input))
		error((t_err){"Invalid float representation", __FILE__, __LINE__, EXIT, 1});
	*f = ft_atof(input);
	if (f < 0)
		error((t_err){"Number out of range: [0, INF]", __FILE__, __LINE__, EXIT, 1});
}

void	parse_range(long double *f, char *input, long double n_lower,
		long double n_upper)
{
	char	s_n_lower[4];
	char	s_n_upper[4];

	if (!f || !input)
		error((t_err){"NULL pointer", __FILE__, __LINE__, EXIT, 1});
	if (!is_valid_number(input))
		error((t_err){"Invalid number representation", __FILE__, __LINE__, EXIT, 1});
	*f = ft_atof(input);
	snprintf(s_n_lower, 4, "%Lf", n_lower);
	snprintf(s_n_upper, 4, "%Lf", n_upper);
	if (!is_in_range_f(*f, n_lower, n_upper))
		error((t_err){"Number out of range", __FILE__, __LINE__, EXIT, 1});
}
