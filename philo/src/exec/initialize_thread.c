/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_thread.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 11:57:14 by rbicanic          #+#    #+#             */
/*   Updated: 2022/04/15 17:17:56 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	init_start_time(t_table *table)
{
	int				i;
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	i = 0;
	while (i < table->philo_nbr)
	{
		(&table->philos[i])->last_eat_time = start_time;
		i++;
	}
}

uint8_t	philo_join_threads(t_table *table, pthread_t *philo_th)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_join(philo_th[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	thread_error(t_table *table, pthread_t *philo_th)
{
	free(philo_th);
	destroy_mutex(table);
}

int	create_philo_threads(t_table *table, pthread_t *philo_th)
{
	int	i;

	i = 0;
	pthread_mutex_lock(table->dead_mutex);
	while (i < table->philo_nbr)
	{
		if (pthread_create(&philo_th[i], NULL,
				&routine, (void *)&table->philos[i]) != 0)
			return (write(2, CREATE_THREAD_MSG, 31),
				thread_error(table, philo_th), 1);
		i++;
	}
	init_start_time(table);
	print_relative_time();
	pthread_mutex_unlock(table->dead_mutex);
	return (0);
}

uint8_t	initialize_threads(t_table *table)
{
	pthread_t		*philo_th;
	int				i;

	philo_th = malloc(sizeof(pthread_t *) * table->philo_nbr);
	if (!philo_th)
		return (write(2, ALLOC_ERR_MSG, 24), 1);
	i = 0;
	if (create_philo_threads(table, philo_th))
		return (1);
	if (philo_join_threads(table, philo_th) == 1)
		return (write(2, JOIN_THREAD_MSG, 29),
			thread_error(table, philo_th), 1);
	destroy_mutex(table);
	free(philo_th);
	return (0);
}
