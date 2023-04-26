/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quadratic_ops.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/26 10:38:04 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/26 11:04:38 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt.h>
#include <stdlib.h>
#include <math.h>

long double	*quad_eq_solver(long double a, long double b, long double c,
		long double *disc)
{
	long double	discriminant;
	long double	*solution;

	discriminant = b * b - 4 * a * c;
	if (disc != NULL)
		*disc = discriminant;
	if (discriminant < 0)
		return (NULL);
	else
	{
		solution = malloc(2 * sizeof(long double));
		if (!solution)
			return (NULL);
		solution[0] = (-b + sqrt(discriminant)) / (2.0 * a);
		solution[1] = (-b - sqrt(discriminant)) / (2.0 * a);
	}
	return (solution);
}
