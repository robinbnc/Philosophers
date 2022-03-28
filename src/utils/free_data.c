/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:02:58 by rbicanic          #+#    #+#             */
/*   Updated: 2022/03/28 19:17:13 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_table(t_table *table)
{
	if (table->dead)
		free(table->dead);
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
}
