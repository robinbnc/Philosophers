/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:33:28 by rbicanic          #+#    #+#             */
/*   Updated: 2022/04/04 17:23:08 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	initialize_philo_forks(t_table *table, t_philo *philos, int i)
{
	philos[i].left_forks = &table->forks[i];
	philos[i].left_forks_mutex = &table->forks_mutex[i];
	if (i != table->philo_nbr - 1)
	{
		philos[i].right_forks = &table->forks[i + 1];
		philos[i].right_forks_mutex = &table->forks_mutex[i + 1];
	}
	else
	{
		philos[i].right_forks = &table->forks[0];
		philos[i].right_forks_mutex = &table->forks_mutex[0];
	}
}

t_philo	*initialize_philo(t_table *table, char *av[], t_philo *philos)
{
	int	i;

	i = 0;
	if (is_over_max(av[1], 1) || is_over_max(av[2], 1)
		|| is_over_max(av[3], 1) || (av[4] && is_over_max(av[4], 1)))
		return (write(2, OVER_INT_MSG, 42), NULL);
	while (i < table->philo_nbr)
	{
		philos[i].philo_id = i;
		philos[i].philo_nbr = table->philo_nbr;
		philos[i].time_to_die = ft_atoi(av[1]);
		philos[i].time_to_eat = ft_atoi(av[2]);
		philos[i].time_to_sleep = ft_atoi(av[3]);
		if (av[4])
			philos[i].nbr_of_meals = ft_atoi(av[4]);
		else
			philos[i].nbr_of_meals = -1;
		initialize_philo_forks(table, philos, i);
		philos[i].dead = table->dead;
		philos[i].dead_mutex = table->dead_mutex;
		philos[i].print_mutex = table->print_mutex;
		i++;
	}
	return (philos);
}

void	initialize_ptr_to_null(t_table *table)
{
	table->dead = NULL;
	table->dead_mutex = NULL;
	table->forks = NULL;
	table->forks_mutex = NULL;
	table->print_mutex = NULL;
	table->philos = NULL;
}

t_table	*initialize_table(t_table *table, char *av[])
{
	initialize_ptr_to_null(table);
	if (is_over_max(*av, 1))
		return (write(2, OVER_INT_MSG, 42), NULL);
	table->philo_nbr = ft_atoi(*av);
	if (table->philo_nbr < 1)
		return (write(2, ONE_PHILO_MSG, 40), NULL);
	if (ft_malloc((void **)&table->dead_mutex, sizeof(pthread_mutex_t)) == 1
		|| ft_malloc((void **)&table->print_mutex, sizeof(pthread_mutex_t)) == 1
		|| ft_malloc((void **)&table->forks_mutex,
			table->philo_nbr * sizeof(pthread_mutex_t)) == 1
		|| ft_malloc((void **)&table->philos,
			sizeof(t_philo) * (table->philo_nbr + 1))
		|| ft_malloc((void **)&table->dead, sizeof(int)) == 1
		|| ft_malloc((void **)&table->forks,
			table->philo_nbr * sizeof(int)) == 1)
		return (NULL);
	*table->dead = 0;
	memset(table->forks, 0, table->philo_nbr * sizeof(int));
	table->philos[table->philo_nbr].philo_id = -1;
	if (!initialize_philo(table, av, table->philos))
		return (NULL);
	return (table);
}

uint8_t	initialize_data(t_table *table, char *av[])
{
	if (!initialize_table(table, av))
		return (free_table(table), 1);
	initialize_mutex(table);
	return (0);
}
