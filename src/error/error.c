/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:50:50 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/13 13:19:24 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mrt_macros.h>
#include <stdio.h>
#include <stdlib.h>

#define RED "\033[0;31m"
#define YLW "\033[0;32m"
#define GRN "\033[1;33m"
#define DEF "\033[0m"

int	error(char	*msg, int exit_method, int exit_code)
{
	printf("%sError%s\n", RED, DEF);
	if (msg)
	{
		printf("%s\n", msg);
		free(msg);
	}
	if (exit_method == EXIT)
		exit(exit_code);
	else if (exit_method == RETURN)
		return (exit_code);
	return (EXIT_FAILURE);
}
