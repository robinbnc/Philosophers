/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:17:18 by rbicanic          #+#    #+#             */
/*   Updated: 2022/04/03 19:54:10 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	check_death(t_philo *philo)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);// peut etre check retour
	if ((current_time.tv_usec - philo->last_eat_time.tv_usec) / 1000
		> philo->time_to_die)
	{
		// printf("\n%ld\n", (current_time.tv_usec - philo->last_eat_time.tv_usec) / 1000);
		ft_print_messages(philo, "is dead\n", RED);
		pthread_mutex_lock(philo->dead_mutex);
		*philo->dead = 1;
		pthread_mutex_unlock(philo->dead_mutex);
	}
}

void	philo_can_eat(t_philo *philo)
{
	*philo->right_forks = 1;
	pthread_mutex_unlock(philo->right_forks_mutex);
	gettimeofday(&philo->last_eat_time, NULL);// check retour potentiellement
	ft_print_messages(philo, EATING_MSG, GREEN);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_lock(philo->left_forks_mutex);
	*philo->left_forks = 0;
	pthread_mutex_unlock(philo->left_forks_mutex);
	pthread_mutex_lock(philo->right_forks_mutex);
	*philo->right_forks = 0;
	pthread_mutex_unlock(philo->right_forks_mutex);
	ft_print_messages(philo, SLEEPING_MSG, BLUE);
	usleep(philo->time_to_sleep * 1000);
	ft_print_messages(philo, THINKING_MSG, YELLOW);
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

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo_is_dead(philo))
	{
		pthread_mutex_lock(philo->left_forks_mutex);
		if (*philo->left_forks == 0 && !philo_is_dead(philo))
		{
			check_death(philo);
			*philo->left_forks = 1;
			pthread_mutex_unlock(philo->left_forks_mutex);
			pthread_mutex_lock(philo->right_forks_mutex);
			if (*philo->right_forks == 0)
				philo_can_eat(philo);
			else
				only_one_fork_available(philo);
		}
		else
			pthread_mutex_unlock(philo->left_forks_mutex);
		check_death(philo);
	}
	return ((void *)1);
}
