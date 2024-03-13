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

	str = ft_strrchr(file_path, '.');
	ft_errors((str == NULL || (ft_strlen(str) != ft_strlen(ext))),
		"Error:\nEl Archivo no tiene extencion .ber");
	ft_errors((ft_strncmp(str, ext, ft_strlen(str))),
		"Error:\nEl Archivo no tiene extencion .ber");
}

void	ft_validate_border(t_game *game, char **matriz_aux)
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
				ft_errors((matriz_aux[i][j] != '1'),
					"Error:\nEl mapa no tiene borde");
			}
			if (j == 0 || j == game->cols - 1)
			{
				ft_errors((matriz_aux[i][j] != '1'),
					"Error:\nEl mapa no tiene borde");
			}
			j++;
		}
		i++;
	}
}

void	ft_validate_rectangle(t_game *game, char **matriz_aux)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			if (game->cols != (int)ft_strlen(matriz_aux[i]))
			{
				//ft_free_map(game->matriz_aux, game->rows);
				ft_errors(1, "Error:\nEl mapa no es un rectangulo");
			}
			if (game->cols < 3 || game->rows < 3)
				ft_errors(1, "Error:\nEl mapa es muy pequeño");
			j++;
		}
		i++;
	}
}

int	ft_validate_lines(t_game *game, char **matriz_aux)
{
	int	i;

	i = 0;
	while (i < game->rows)
	{
		if (matriz_aux[i] == NULL || matriz_aux[i][0] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	ft_validate_map(t_game *game)
{
	ft_errors(ft_validate_lines(game, game->matriz_aux),
		"Error:\nEl mapa no tiene lineas validas");
	ft_validate_rectangle(game, game->matriz_aux);
	ft_validate_border(game, game->matriz_aux);
	ft_validate_objects(game, game->matriz_aux);
	ft_browse_map(game, game->matriz_aux, game->player.x, game->player.y);
	ft_check_browse(game, game->matriz_aux);
	ft_free_map(game->matriz_aux, game->rows);
	return (0);
}
