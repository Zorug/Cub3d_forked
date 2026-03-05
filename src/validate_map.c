/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 18:34:00 by tnuno-mo          #+#    #+#             */
/*   Updated: 2026/03/05 21:18:41 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"


// Checks if a character is valid in the map.
// Valid characters: '0', '1', 'N', 'S', 'E', 'W', and space.
int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}


// Checks if a character represents a player start position.
// Valid player characters: 'N', 'S', 'E', 'W'.
int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}


// Counts the number of player start positions in the map.
// Returns the count of 'N', 'S', 'E', or 'W' found.
int	count_player_positions(char **map)
{
       int i;
       int j;
       int count;

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


// Checks if a line contains only valid map characters.
// Returns 1 if valid, 0 otherwise.
int	is_line_map(const char *line)
{
       int i;

       i = 0;
       while (line[i])
       {
	       if (!is_valid_map_char(line[i]))
		       return (0);
	       i++;
       }
       return (1);
}

// Helper to get char at position, returns ' ' if out of bounds
static char	get_map_char(char **map, int i, int j)
{
	if (!map[i])
		return (' ');
	if (j < 0 || j >= (int)ft_strlen(map[i]))
		return (' ');
	return (map[i][j]);
}

// Check if position is surrounded by walls (flood fill concept)
static int	is_position_valid(char **map, int i, int j)
{
	char	c;
	char	up;
	char	down;
	char	left;
	char	right;

	c = get_map_char(map, i, j);
	if (c != '0' && !is_player_char(c))
		return (1);
	if (i == 0 || j == 0)
		return (0);
	up = get_map_char(map, i - 1, j);
	down = get_map_char(map, i + 1, j);
	left = get_map_char(map, i, j - 1);
	right = get_map_char(map, i, j + 1);
	if (up != '0' && up != '1' && !is_player_char(up))
		return (0);
	if (down != '0' && down != '1' && !is_player_char(down))
		return (0);
	if (left != '0' && left != '1' && !is_player_char(left))
		return (0);
	if (right != '0' && right != '1' && !is_player_char(right))
		return (0);
	return (1);
}

// Checks if the map is closed (surrounded by walls).
// Returns 1 if the map is closed, 0 otherwise.
// Spaces inside the map are treated as void - walkable areas cannot touch them.
int	is_map_closed(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_position_valid(map, i, j))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}


// Validates the map by checking:
// - All characters are valid
// - Exactly one player start position exists
// - The map is closed by walls
// Returns 1 if the map is valid, 0 otherwise.
int	validate_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		if (!is_line_map(map[i]))
			return (0);
		i++;
	}
	if (count_player_positions(map) != 1)
		return (0);
	if (!is_map_closed(map))
		return (0);
	return (1);
}
