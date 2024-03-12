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
	ft_free_img(game);
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

void	ft_free_img(t_game *game)
{
	int	i;

	i = 0;
	while (i < NUM_FRAMES)
	{
		mlx_destroy_image(game->mlx, game->player.front[i].img);
		mlx_destroy_image(game->mlx, game->player.left[i].img);
		mlx_destroy_image(game->mlx, game->player.right[i].img);
		mlx_destroy_image(game->mlx, game->player.up[i].img);
		mlx_destroy_image(game->mlx, game->player.down[i].img);
		mlx_destroy_image(game->mlx, game->wall[i].img);
		i++;
	}
	mlx_destroy_image(game->mlx, game->exit.img);
	mlx_destroy_image(game->mlx, game->collectible.img);
	mlx_destroy_image(game->mlx, game->floor.img);
}

void	ft_free_map(char **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	ft_errors(bool if_error, char *str)
{
	if (if_error)
	{
		perror(str);
		exit(EXIT_FAILURE);
	}
}
