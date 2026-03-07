/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstdelone.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/12 20:14:48 by tnuno-mo		  #+#	#+#			 */
/*   Updated: 2024/11/12 20:48:35 by tnuno-mo		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL || del == NULL)
		return ;
	(*del)(lst -> content);
	free(lst);
}
