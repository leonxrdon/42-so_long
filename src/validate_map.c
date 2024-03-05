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

#include "../include/so_long.h"

int	ft_validate_ext(char *file_path, char *ext)
{
	char	*str;
	size_t	i;

	i = 0;
	str = ft_strrchr(file_path, '.');
	return (ft_strncmp(str, ext, ft_strlen(str)));
}
