/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:02:58 by rbicanic          #+#    #+#             */
/*   Updated: 2022/04/03 15:38:07 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_table(t_table *table)
{
	if (table->dead != NULL)
		free(table->dead);
	if (table->forks != NULL)
		free(table->forks);
	if (table->dead_mutex != NULL)
		free(table->dead_mutex);
	if (table->forks_mutex != NULL)
		free(table->forks_mutex);
	if (table->print_mutex != NULL)
		free(table->print_mutex);
	if (table->philos != NULL)
		free(table->philos);
}
