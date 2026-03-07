/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 23:14:12 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 15:38:47 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_scene_config(t_scene_config *cfg)
{
	if (cfg->no_path)
		free(cfg->no_path);
	if (cfg->so_path)
		free(cfg->so_path);
	if (cfg->we_path)
		free(cfg->we_path);
	if (cfg->ea_path)
		free(cfg->ea_path);
	cfg->no_path = NULL;
	cfg->so_path = NULL;
	cfg->we_path = NULL;
	cfg->ea_path = NULL;
}

int	error_return(const char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd((char *)message, 2);
	return (0);
}

void	error_exit(t_data *data, const char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd((char *)message, 2);
	if (data)
		cleanup_and_exit(data, 1);
	exit(1);
}