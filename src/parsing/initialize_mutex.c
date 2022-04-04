/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_mutex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:50:23 by rbicanic          #+#    #+#             */
/*   Updated: 2022/04/04 17:23:07 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	initialize_mutex(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_init(table->dead_mutex, NULL);
	pthread_mutex_init(table->print_mutex, NULL);
	while (i < table->philo_nbr)
	{
		pthread_mutex_init(&table->forks_mutex[i], NULL);
		i++;
	}
}

void	destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(table->dead_mutex);
	pthread_mutex_destroy(table->print_mutex);
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->forks_mutex[i]);
		i++;
	}
}
