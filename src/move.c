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

#include "../include/so_long.h"

void	ft_player_move(t_game *game, int i, int j, int x, int y)
{
	if (game->map[x][y] == '1')
	{
		printf("No se puede mover\n");
	}
	else if (game->map[x][y] == 'C')
	{
		game->player.moves++;
		game->collectibles--;
		game->map[x][y] = 'P';
		game->map[i][j] = '0';
		printf("Se ha recogido una moneda\n");
	}
	else if (game->map[x][y] == 'E')
	{
		if (game->collectibles <= 0)
		{
			printf("Se ha llegado a la salida\n");
			exit(0);
		}
		else
			printf("No se puede salir\n");
	}
	else if (game->map[x][y] == '0')
	{
		game->player.moves++;
		game->collectibles--;
		game->map[x][y] = 'P';
		game->map[i][j] = '0';
	}
	ft_draw_map(game);
}

int	ft_move(int keycode, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			if (game->map[i][j] == 'P')
			{
				if (keycode == 123 || keycode == 0)
				{
					printf("Izquierda\n");
					ft_player_move(game, i, j, i, j - 1);
				}
				else if (keycode == 124 || keycode == 2)
				{
					printf("Derecha\n");
					ft_player_move(game, i, j, i, j + 1);
				}
				else if (keycode == 125 || keycode == 1)
				{
					printf("Abajo\n");
					ft_player_move(game, i, j, i + 1, j);
				}
				else if (keycode == 126 || keycode == 13)
				{
					printf("Arriba\n");
					ft_player_move(game, i, j, i - 1, j);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}
