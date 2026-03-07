/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstiter.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/12 20:31:34 by tnuno-mo		  #+#	#+#			 */
/*   Updated: 2024/11/12 21:24:18 by tnuno-mo		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

// Implement function to iterate over the list & apply  'f' to each node.
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		f(lst -> content);
		lst = lst -> next;
	}
}
