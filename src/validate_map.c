/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 18:34:00 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/07 20:50:34 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Check if a map character is valid. */
int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

/* Check if a character is a player start marker. */
int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/* Count player start positions in the map. */
int	count_player_positions(char **map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player_char(map[i][j]))
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

/* Verify if the map is closed by walls/spaces. */
int	is_map_closed(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '1' || map[i][j] == ' ')
				continue ;
			if (i == 0 || j == 0 || !map[i + 1] || !map[i][j + 1])
				return (0);
			if ((int)ft_strlen(map[i - 1]) <= j
				|| (int)ft_strlen(map[i + 1]) <= j)
				return (0);
			if (map[i][j - 1] == ' ' || map[i][j + 1] == ' '
				|| map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
				return (0);
		}
	}
	return (1);
}

/* Validate map content, player count and enclosure. */
int	validate_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid_map_char(map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	if (count_player_positions(map) != 1)
		return (0);
	if (!is_map_closed(map))
		return (0);
	return (1);
}
