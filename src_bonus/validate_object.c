/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_object.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnarvaez <lnarvaez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 11:39:20 by lnarvaez          #+#    #+#             */
/*   Updated: 2024/03/13 11:39:22 by lnarvaez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_player_inmap(t_game *game, char **matriz_aux)
{
	int	i;
	int	j;
	int	c_player;

	i = 0;
	c_player = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			if (matriz_aux[i][j] == 'P')
			{
				game->player.x = j;
				game->player.y = i;
				c_player++;
			}
			j++;
		}
		i++;
	}
	return (c_player);
}

int	ft_exit_inmap(t_game *game, char **matriz_aux)
{
	int	i;
	int	j;
	int	c_exit;

	i = 0;
	c_exit = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			if (matriz_aux[i][j] == 'E')
			{
				game->exit_x = j;
				game->exit_y = i;
				c_exit++;
			}
			j++;
		}
		i++;
	}
	return (c_exit);
}

int	ft_collect_inmap(t_game *game, char **matriz_aux)
{
	int	i;
	int	j;
	int	c_collect;

	i = 0;
	c_collect = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			if (matriz_aux[i][j] == 'C')
				c_collect++;
			j++;
		}
		i++;
	}
	game->collectibles = c_collect;
	return (c_collect);
}

void	ft_validate_objects(t_game *game, char **matriz_aux)
{
	int	i;
	int	j;

	ft_errors((ft_player_inmap(game, matriz_aux) != 1),
		"Error:\nNumero de jugadores incorrecto");
	ft_errors((ft_exit_inmap(game, matriz_aux) != 1),
		"Error:\nEl mapa no tiene una salida válida");
	ft_errors((ft_collect_inmap(game, matriz_aux) == 0),
		"Error:\nEl mapa no tiene coleccionables");
	i = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			if (matriz_aux[i][j] == '0' || matriz_aux[i][j] == '1'
					|| matriz_aux[i][j] == 'C' || matriz_aux[i][j] == 'E'
					|| matriz_aux[i][j] == 'P')
				;
			else
				ft_errors(1, "Error:\nEl mapa tiene objetos invalidos");
			j++;
		}
		i++;
	}
}
