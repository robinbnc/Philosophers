/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_thread.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 11:57:14 by rbicanic          #+#    #+#             */
/*   Updated: 2022/04/03 18:27:22 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_start_time(t_table *table)
{
	int				i;
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);// peut etre check retour
	i = 0;
	while (i < table->philo_nbr)
	{
		(&table->philos[i])->last_eat_time = start_time;
		i++;
	}
}

uint8_t	initialize_threads(t_table *table)
{
	pthread_t		*philo_th;
	int				i;

	philo_th = malloc(sizeof(pthread_t *) * table->philo_nbr);
	if (!philo_th)
		return (write(2, ALLOC_ERR_MSG, 24), 1);
	i = 0;
	init_start_time(table);
	while (i < table->philo_nbr)
	{
		if (pthread_create(&philo_th[i], NULL,
				&routine, (void *)&table->philos[i]) != 0)
			return (write(2, CREATE_THREAD_MSG, 31), free(philo_th), 1);
		i++;
	}
	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_join(philo_th[i], NULL) != 0)
			return (write(2, JOIN_THREAD_MSG, 29), free(philo_th), 1);
		i++;
	}
	destroy_mutex(table);
	free(philo_th);
	return (0);
}
