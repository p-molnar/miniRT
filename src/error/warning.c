/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   warning.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:50:50 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/19 12:34:10 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <mrt_macros.h>
#include <stdio.h>
#include <stdlib.h>

#define YLW "\033[93m"
#define DEF "\033[0m"

void	warning(char *msg)
{
	printf("%sWarning%s\n", YLW, DEF);
	if (msg)
	{
		printf("%s\n", msg);
		free(msg);
	}
}
