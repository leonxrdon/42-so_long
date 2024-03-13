/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charge_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnarvaez <lnarvaez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:48:38 by lnarvaez          #+#    #+#             */
/*   Updated: 2024/03/05 15:48:44 by lnarvaez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_make_map(t_game *game, int fd)
{
	char	*gnl;
	int		rows;
	int		cols;

	rows = 0;
	cols = 0;
	gnl = get_next_line(fd);
	while (gnl != NULL)
	{
		rows++;
		cols = (ft_strlen(gnl) - 1);
		free(gnl);
		gnl = get_next_line(fd);
	}
	game->rows = rows;
	game->cols = cols;
	game->matriz_aux = (char **)malloc(sizeof(char *) * rows + 1);
	if (game->matriz_aux == NULL)
		ft_errors(1, "Error:\nNo se pudo reservar memoria para el mapa");
	game->map = (char **)malloc(sizeof(char *) * rows + 1);
	if (game->map == NULL)
		ft_errors(1, "Error:\nNo se pudo reservar memoria para el mapa");
	close(fd);
}

char	*ft_build_path(char *base_path, int frame_number)
{
	char	*frame_path;
	char	*full_path;

	frame_path = ft_strjoin(base_path, ft_itoa(frame_number));
	full_path = ft_strjoin(frame_path, ".xpm");
	free(frame_path);
	return (full_path);
}

void	ft_charge_map(t_game *game, char *file_path)
{
	char		*gnl;
	int			i;
	int			fd;

	fd = open(file_path, O_RDONLY);
	ft_errors((fd < 0), "Error:\nEl Archivo no existe o se se puede abrir");
	gnl = get_next_line(fd);
	i = 0;
	while (gnl != NULL && gnl[0] != '\0' && i < game->rows)
	{
		game->matriz_aux[i] = *ft_split(gnl, '\n');
		free(gnl);
		gnl = get_next_line(fd);
		i++;
	}
	close(fd);
}
