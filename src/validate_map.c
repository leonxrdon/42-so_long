/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnarvaez <lnarvaez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:49:08 by lnarvaez          #+#    #+#             */
/*   Updated: 2024/03/05 15:49:10 by lnarvaez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_validate_ext(char *file_path, char *ext)
{
	char	*str;
	size_t	i;

	i = 0;
	str = ft_strrchr(file_path, '.');
	return (ft_strncmp(str, ext, ft_strlen(str)));
}

int	ft_validate_border(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			if (i == 0 || i == game->rows - 1)
			{
				if (game->map[i][j] != '1')
				{
					printf("Error en el borde\n");
					exit(EXIT_FAILURE);
				}
			}
			if (j == 0 || j == game->cols - 1)
			{
				if (game->map[i][j] != '1')
				{
					printf("Error en el borde\n");
					exit(EXIT_FAILURE);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}


int	ft_validate_map(t_game *game)
{
	int	i;
	int	j;
	int	cout_player;
	int	cout_exit;
	int	cout_collectible;

	i = 0;
	cout_player = 0;
	cout_exit = 0;
	cout_collectible = 0;
	ft_validate_border(game);
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			if (game->map[i][j] == 'P')
			{
				game->player.x = i;
				game->player.y = j;
				cout_player++;
			}
			if (game->map[i][j] == 'E')
				cout_exit++;
			if (game->map[i][j] == 'C')
				cout_collectible++;
			j++;
		}
		i++;
	}
	ft_browse_map(game, game->player.x, game->player.y);
	ft_check_browe(game);
	printf("Player: %d, Exit: %d, Collectibles: %d\n", cout_player, cout_exit, cout_collectible);
	if (cout_player != 1 || cout_exit != 1 || cout_collectible < 1)
	{
		printf("Error en el mapa\n");
		exit(1);
	}
	game->collectibles = cout_collectible;
	printf("Collectibles: %d\n", game->collectibles);
	return (0);
}
