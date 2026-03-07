/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstadd_front.c								  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/12 19:17:54 by tnuno-mo		  #+#	#+#			 */
/*   Updated: 2024/11/12 19:53:53 by tnuno-mo		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

// Creates and add "*new" to the begiining of the list
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new || !lst)
		return ;
	new -> next = *lst;
	*lst = new;
}
