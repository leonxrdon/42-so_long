/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_conections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnarvaez <lnarvaez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:28:30 by lnarvaez          #+#    #+#             */
/*   Updated: 2024/03/08 13:28:31 by lnarvaez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_browse_map(t_game *game, char **matriz_aux, int row, int col)
{
	if (row < 0 || row >= game->rows)
		ft_errors(1, "Error:\nEl mapa es invalido");
	if (col < 0 || col >= game->cols)
		ft_errors(1, "Error:\nEl mapa es invalido");
	if (matriz_aux[row][col] == '1' || matriz_aux[row][col] == 'V')
	{
		return (0);
	}
	if (matriz_aux[row][col] == '0')
	{
		matriz_aux[row][col] = 'V';
	}
	if (matriz_aux[row][col] == 'C' || matriz_aux[row][col] == 'E')
		matriz_aux[row][col] = 'V';
	return (ft_browse_map(game, matriz_aux, row + 1, col)
		|| ft_browse_map(game, matriz_aux, row - 1, col)
		|| ft_browse_map(game, matriz_aux, row, col + 1)
		|| ft_browse_map(game, matriz_aux, row, col - 1));
}

void	ft_check_browse(t_game *game, char **matriz_aux)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			if (matriz_aux[i][j] == 'E' || matriz_aux[i][j] == 'C')
				ft_errors(1, "Error:\nEl mapa no puede ser terminado");
			j++;
		}
		i++;
	}
}
