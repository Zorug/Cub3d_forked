/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   validate_map.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/02/15 18:34:00 by tnuno-mo		  #+#	#+#			 */
/*   Updated: 2026/03/01 01:17:35 by tnuno-mo		 ###   ########.fr	   */
/*																			*/
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

// Checks if the map is closed (surrounded by walls).
// Returns 1 if the map is closed, 0 otherwise.
// Spaces are treated as outside the map and must not touch '0' or player positions.
int	is_map_closed(char **map)
{
	   int i;
	   int j;
	   int len;

	   i = 0;
	   while (map[i])
	   {
		   len = (int)ft_strlen(map[i]);
		   j = 0;
		   while (j < len)
		   {
			   if (map[i][j] == '0' || is_player_char(map[i][j]))
			   {
				   if (i == 0 || j == 0 || !map[i + 1] || j + 1 >= (int)ft_strlen(map[i]))
					   return (0);
				   if ((j - 1 < 0 || map[i][j - 1] == ' ') ||
					   (map[i][j + 1] == ' ') ||
					   (i - 1 < 0 || (int)ft_strlen(map[i - 1]) <= j || map[i - 1][j] == ' ') ||
					   (!map[i + 1] || (int)ft_strlen(map[i + 1]) <= j || map[i + 1][j] == ' '))
					   return (0);
			   }
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
