/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strlcat.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/10/27 22:29:49 by tnuno-mo		  #+#	#+#			 */
/*   Updated: 2024/11/05 19:33:20 by tnuno-mo		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

//concatenate two strings with a limit of "size"
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen((char *)src);
	if (size <= len_dst)
		return (size + len_src);
	i = 0;
	while (src[i] && ((len_dst + i) < (size - 1)))
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}
