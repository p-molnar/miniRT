/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   range.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/26 10:57:31 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/26 10:57:46 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	is_in_range_f(long double n, long double n_lower, long double n_upper)
{
	return (n >= n_lower && n <= n_upper);
}

int	is_in_range_i(int n, int n_lower, int n_upper)
{
	return (n >= n_lower && n <= n_upper);
}
