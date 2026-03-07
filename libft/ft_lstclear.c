/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstclear.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/12 20:19:46 by tnuno-mo		  #+#	#+#			 */
/*   Updated: 2024/11/12 22:15:10 by tnuno-mo		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

// Clears the list and frees all the nodes
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*curr_node;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		curr_node = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(curr_node, del);
	}
}
