/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnarvaez <lnarvaez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:42:59 by lnarvaez          #+#    #+#             */
/*   Updated: 2024/03/11 14:43:01 by lnarvaez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_close_esc(t_game *game)
{
	ft_free_map(game->map, game->rows);
	ft_free_img(game);
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

void	ft_free_img(t_game *game)
{
	mlx_destroy_image(game->mlx, game->player.sprite.img);
	mlx_destroy_image(game->mlx, game->exit.img);
	mlx_destroy_image(game->mlx, game->collectible.img);
	mlx_destroy_image(game->mlx, game->floor.img);
}

void	ft_errors(bool if_error, char *str)
{
	if (if_error)
	{
		perror(str);
		exit(EXIT_FAILURE);
	}
}

void	ft_free_map(char **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

void	ft_free_matriz(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->rows)
	{
		free(game->matriz_aux[i]);
		i++;
	}
	free(game->matriz_aux);
}
