/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuno-mo <tnuno-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:29:35 by tnuno-mo          #+#    #+#             */
/*   Updated: 2025/03/14 04:26:05 by tnuno-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long int	ft_atol(const char *nbr)
{
	int			i;
	int			sign;
	long int	res;

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
