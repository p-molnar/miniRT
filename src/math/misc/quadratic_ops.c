/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quadratic_ops.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/26 10:38:04 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/11 10:17:48 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <minirt.h>
#include <stdlib.h>
#include <math.h>

long double	*quad_eq_solver(t_quad_param param, long double *disc)
{
	long double	discriminant;
	long double	*solution;

	discriminant = pow(param.b, 2) - 4 * param.a * param.c;
	solution = NULL;
	if (disc != NULL)
		*disc = discriminant;
	if (discriminant >= 0)
	{
		solution = malloc(2 * sizeof(long double));
		if (!solution)
			return (NULL);
		solution[0] = (-param.b + sqrt(discriminant)) / (2.0 * param.a);
		solution[1] = (-param.b - sqrt(discriminant)) / (2.0 * param.a);
	}
	return (solution);
}
