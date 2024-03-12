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

void	ft_validate_ext(char *file_path, char *ext)
{
	char	*str;
	size_t	i;

	i = 0;
	str = ft_strrchr(file_path, '.');
	ft_errors((str == NULL || (ft_strlen(str) != ft_strlen(ext))),
		"Error:\nEl Archivo no tiene extencion .ber");
	ft_errors((ft_strncmp(str, ext, ft_strlen(str))),
		"Error:\nEl Archivo no tiene extencion .ber");
}

void	ft_validate_border(t_game *game)
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
				ft_errors((game->map[i][j] != '1'),
					"Error:\nEl mapa no tiene borde");
			}
			if (j == 0 || j == game->cols - 1)
			{
				ft_errors((game->map[i][j] != '1'),
					"Error:\nEl mapa no tiene borde");
			}
			j++;
		}
		i++;
	}
}

void	ft_validate_rectangle(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			if (game->cols != (int)ft_strlen(game->map[i]))
				ft_errors(1, "Error:\nEl mapa no es un rectangulo");
			j++;
		}
		i++;
	}
}

void	ft_validate_objects(t_game *game)
{
	int	i;
	int	j;
	int	c_player;
	int	c_exit;
	int	c_collectible;

	i = 0;
	c_player = 0;
	c_exit = 0;
	c_collectible = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			if (game->map[i][j] == 'P')
			{
				game->player.x = j;
				game->player.y = i;
				c_player++;
			}
			else if (game->map[i][j] == 'E')
			{
				game->exit_x = j;
				game->exit_y = i;
				c_exit++;
			}
			else if (game->map[i][j] == 'C')
				c_collectible++;
			else if (game->map[i][j] == '0' || game->map[i][j] == '1')
				;
			else
				ft_errors(1, "Error:\nEl mapa tiene objetos invalidos");
			j++;
		}
		i++;
	}
	ft_errors((c_player != 1), "Error:\nEl mapa no tiene el numero de jugadores correcto");
	ft_errors((c_exit != 1), "Error:\nEl mapa no tiene una salida válida");
	ft_errors((c_collectible == 0), "Error:\nEl mapa no tiene coleccionables");
	game->collectibles = c_collectible;
}

int	ft_validate_map(t_game *game)
{
	char	**matriz_aux;

	ft_validate_rectangle(game);
	ft_validate_border(game);
	ft_validate_objects(game);
	matriz_aux = ft_matriz_aux(game);
	ft_browse_map(game, matriz_aux, game->player.x, game->player.y);
	ft_check_browse(game, matriz_aux);
	return (0);
}
