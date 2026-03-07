/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstadd_back.c								   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/12 19:58:44 by tnuno-mo		  #+#	#+#			 */
/*   Updated: 2024/11/12 22:11:48 by tnuno-mo		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!new)
		return ;
	if (!lst || !(*lst))
		*lst = new;
	else
	{
		temp = ft_lstlast(*lst);
		temp -> next = new;
	}
}
