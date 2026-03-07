/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_atoi.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/03 13:08:51 by tnuno-mo		  #+#	#+#			 */
/*   Updated: 2025/03/14 04:25:50 by tnuno-mo		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

// 
int	ft_atoi(const char *nbr)
{
	int		i;
	int		sign;
	int		res;

	i = 0;
	sign = 1;
	res = 0;
	while (nbr[i] == '\f' || nbr[i] == '\n' || nbr[i] == '\r'
		|| nbr[i] == '\t' || nbr[i] == '\v' || nbr[i] == ' ')
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			sign = -1;
		i++;
	}
	while ((nbr[i] >= '0') && nbr[i] <= '9')
	{
		res = (res * 10) + (nbr[i] - '0');
		i++;
	}
	return (res * sign);
}

/* 
int	main(void)
{
	char *str = "0hzh";
	printf("%d\n", ft_atoi(str));
	printf("%d\n", atoi(str));
	return (0);
}
 */