/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 17:33:28 by rbicanic          #+#    #+#             */
/*   Updated: 2022/03/28 20:37:07 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_philo	*initialize_philo(t_table *table, char *av[], t_philo *philos)
{
	int	i;

	i = 0;
	if (is_over_max(av[1], 1) || is_over_max(av[2], 1)
		|| is_over_max(av[3], 1) || is_over_max(av[4], 1))
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
		philos[i].forks = table->forks;
		philos[i].dead = table->dead;
		i++;
	}
	return (philos);
}

//passer av[1] + peut etre check que les vqleurs sont inferieur a int
t_table	*initialize_table(t_table *table, char *av[])
{
	table->dead = NULL;
	table->forks = NULL;
	table->philos = NULL;
	if (is_over_max(*av, 1))
		return (write(2, OVER_INT_MSG, 42), NULL);
	table->philo_nbr = ft_atoi(*av);
	if (table->philo_nbr < 1)
		return (write(2, ONE_PHILO_MSG, 40), NULL);
	table->dead = malloc(sizeof(int));
	if (!table->dead)
		return (write(2, ALLOC_ERR_MSG, 24), NULL);
	*table->dead = 0;
	table->forks = malloc(sizeof(int) * table->philo_nbr);
	if (!table->forks)
		return (write(2, ALLOC_ERR_MSG, 24), NULL);
	memset(table->forks, 0, table->philo_nbr * sizeof(int));
	table->philos = malloc(sizeof(t_philo) * (table->philo_nbr + 1));
	if (!table->philos)
		return (write(2, ALLOC_ERR_MSG, 24), NULL);
	table->philos[table->philo_nbr].philo_id = -1;
	if (!initialize_philo(table, av, table->philos))
		return (NULL);
	return (table);
}
