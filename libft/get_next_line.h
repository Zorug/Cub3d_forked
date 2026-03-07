/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line.h									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/12/08 15:19:14 by tnuno-mo		  #+#	#+#			 */
/*   Updated: 2025/03/23 23:33:57 by tnuno-mo		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// values can be redefined when compiling with: "-D BUFFER_SIZE=n"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 46
# endif

//libraries
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

//functions
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

#endif
