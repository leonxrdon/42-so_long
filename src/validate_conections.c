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

int	ft_browse_map(t_game *game, int row, int col)
{
	if (row < 0 || row >= game->rows)
	{
		printf("Error en las conexiones\n");
		exit(EXIT_FAILURE);
	}
	if (col < 0 || col >= game->cols)
	{
		printf("Error en las conexiones\n");
		exit(EXIT_FAILURE);
	}
	if (game->map[row][col] == '1' || game->map[row][col] == 'V')
	{
		//printf("Encountered wall\n");
		return (0);
	}
	if (game->map[row][col] == '0')
	{
		printf("Encountered floor\n");
		game->map[row][col] = 'V';
		//return (0);
	}
	if (game->map[row][col] == 'C' || game->map[row][col] == 'E')
	{
		printf("Encountered collectible or exit\n");
		game->map[row][col] = 'V';
	}
	for (int i = 0; i < game->rows; ++i) {
        for (int j = 0; j < game->cols; ++j) {
            printf("%c ", game->map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
	//return(0);
	return (ft_browse_map(game, row + 1, col) ||	// Abajo
			ft_browse_map(game, row - 1, col) ||	// Arriba
			ft_browse_map(game, row, col + 1) ||	// Derecha
			ft_browse_map(game, row, col - 1));	// Izquierda
}

int	ft_check_browe(t_game *game)
{
	printf("Checking browse\n");
	int	i;
	int	j;

	i = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			if (game->map[i][j] == 'C' || game->map[i][j] == 'E')
			{
				printf("Las esferas o la salida esta obstruida\n");
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (1);
}
