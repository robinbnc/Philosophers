/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:33:14 by rbicanic          #+#    #+#             */
/*   Updated: 2022/04/04 17:23:06 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (!argument_are_valid(argc, argv))
		return (0);
	if (initialize_data(&table, &argv[1]))
		return (1);
	if (initialize_threads(&table) == 1)
		return (free_table(&table), 1);
	free_table(&table);
	return (0);
}
