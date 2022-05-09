/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:59:04 by rbicanic          #+#    #+#             */
/*   Updated: 2022/03/28 20:30:03 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

uint8_t	is_numeric(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

uint8_t	numeric_and_args_exist(char *av[])
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!ft_strlen(av[i]))
			return (write(2, EMPTY_ARG_MSG, 37), 0);
		if (!is_numeric(av[i]))
			return (write(2, NUMERIC_ARG_MSG, 35), 0);
		i++;
	}
	return (1);
}

uint8_t	argument_are_valid(int ac, char *av[])
{
	if (ac < 5 || ac > 6)
		return (write(2, ARG_NBR_MSG, 35), 0);
	if (!numeric_and_args_exist(av))
		return (0);
	return (1);
}
