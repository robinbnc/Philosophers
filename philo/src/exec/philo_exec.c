/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:17:18 by rbicanic          #+#    #+#             */
/*   Updated: 2022/05/09 19:27:47 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	philo_can_eat(t_philo *philo)
{
	if (ft_print_messages(philo, EATING_MSG, GREEN, 0))
		return ;
	gettimeofday(&philo->last_eat_time, NULL);
	usleep(philo->time_to_eat * 1000);
	if (philo->nbr_of_meals > -1)
		philo->nbr_of_meals--;
	pthread_mutex_lock(philo->left_forks_mutex);
	*philo->left_forks = 0;
	pthread_mutex_unlock(philo->left_forks_mutex);
	pthread_mutex_lock(philo->right_forks_mutex);
	*philo->right_forks = 0;
	pthread_mutex_unlock(philo->right_forks_mutex);
	if (ft_print_messages(philo, SLEEPING_MSG, BLUE, 0))
		return ;
	usleep(die_sleeping(philo) * 1000);
	if (ft_print_messages(philo, THINKING_MSG, YELLOW, 0))
		return ;
	if (philo->time_to_eat > philo->time_to_sleep
		&& die_sleeping(philo) > (philo->time_to_eat - philo->time_to_sleep))
		usleep(1010 * (philo->time_to_eat - philo->time_to_sleep));
	else
		usleep(1000);
}

void	only_one_fork_available(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_forks_mutex);
	pthread_mutex_lock(philo->left_forks_mutex);
	*philo->left_forks = 0;
	pthread_mutex_unlock(philo->left_forks_mutex);
}

uint8_t	philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_mutex);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_mutex);
	return (0);
}

uint8_t	take_forks(t_philo *philo)
{
	while (!philo_is_dead(philo))
	{
		pthread_mutex_lock(philo->left_forks_mutex);
		if (*philo->left_forks == 0 && !philo_is_dead(philo))
		{
			*philo->left_forks = 1;
			pthread_mutex_unlock(philo->left_forks_mutex);
			pthread_mutex_lock(philo->right_forks_mutex);
			if (*philo->right_forks == 0 && !philo_is_dead(philo))
			{
				ft_print_messages(philo, FORK_MSG, MAGENTA, 0);
				ft_print_messages(philo, FORK_MSG, MAGENTA, 0);
				*philo->right_forks = 1;
				pthread_mutex_unlock(philo->right_forks_mutex);
				return (1);
			}
			else
				only_one_fork_available(philo);
		}
		else
			pthread_mutex_unlock(philo->left_forks_mutex);
		usleep(10);
		check_death(philo);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->dead_mutex);
	pthread_mutex_unlock(philo->dead_mutex);
	if (philo->philo_id % 2 == 0)
		usleep(30000);
	while (!philo_is_dead(philo) && philo->nbr_of_meals != 0)
	{
		if (take_forks(philo))
			philo_can_eat(philo);
	}
	return ((void *)1);
}
