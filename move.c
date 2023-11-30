/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnarvaez <lnarvaez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:05:36 by lnarvaez          #+#    #+#             */
/*   Updated: 2023/11/30 18:05:38 by lnarvaez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


int	move(int keycode, t_vars *vars)
{
	printf("Tecla: %d\n", keycode);
	if (keycode == 123)
		printf("<\n");
	else if (keycode == 124)
		printf(">\n");
	else if (keycode == 125)
		printf("v\n");
	else if (keycode == 126)
		printf("^\n");
	vars = NULL;
	return (0);
}
