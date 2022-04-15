/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:17:18 by rbicanic          #+#    #+#             */
/*   Updated: 2022/04/15 12:55:16 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	check_death(t_philo *philo)
{
	long int		milli_time;
	struct timeval	current_time;
	struct timeval	last_eat_time;

	last_eat_time = philo->last_eat_time;
	gettimeofday(&current_time, NULL);
	milli_time = (current_time.tv_sec) * 1000 + (current_time.tv_usec) / 1000
		- (((last_eat_time.tv_sec) * 1000 + (last_eat_time.tv_usec) / 1000));
	if (milli_time > philo->time_to_die && !philo_is_dead(philo))
	{
		pthread_mutex_lock(philo->dead_mutex);
		if (*philo->dead == 1)
		{
			pthread_mutex_unlock(philo->dead_mutex);
			return ;
		}
		*philo->dead = 1;
		pthread_mutex_unlock(philo->dead_mutex);
		ft_print_messages(philo, DEATH_MSG, RED, 1);
	}
}

void	philo_can_eat(t_philo *philo)
{
	*philo->right_forks = 1;
	pthread_mutex_unlock(philo->right_forks_mutex);
	if (!philo_is_dead(philo))
		ft_print_messages(philo, EATING_MSG, GREEN, 0);
	if (philo->nbr_of_meals > -1)
		philo->nbr_of_meals--;
	gettimeofday(&philo->last_eat_time, NULL);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_lock(philo->left_forks_mutex);
	*philo->left_forks = 0;
	pthread_mutex_unlock(philo->left_forks_mutex);
	pthread_mutex_lock(philo->right_forks_mutex);
	*philo->right_forks = 0;
	pthread_mutex_unlock(philo->right_forks_mutex);
	if (!philo_is_dead(philo))
		ft_print_messages(philo, SLEEPING_MSG, BLUE, 0);
	usleep(philo->time_to_sleep * 1000);
	if (!philo_is_dead(philo))
		ft_print_messages(philo, THINKING_MSG, YELLOW, 0);
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
	pthread_mutex_lock(philo->dead_mutex);
	pthread_mutex_unlock(philo->dead_mutex);
	if (philo->philo_id % 2 == 0)
		usleep(400);
	while (!philo_is_dead(philo) && philo->nbr_of_meals != 0)
	{
		pthread_mutex_lock(philo->left_forks_mutex);
		if (*philo->left_forks == 0 && !philo_is_dead(philo))
		{
			check_death(philo);
			*philo->left_forks = 1;
			pthread_mutex_unlock(philo->left_forks_mutex);
			pthread_mutex_lock(philo->right_forks_mutex);
			if (*philo->right_forks == 0 && !philo_is_dead(philo))
			{
				ft_print_messages(philo, FORK_MSG, MAGENTA, 0);
				ft_print_messages(philo, FORK_MSG, MAGENTA, 0);
				philo_can_eat(philo);
			}
			else
				only_one_fork_available(philo);
		}
		else
			pthread_mutex_unlock(philo->left_forks_mutex);
		check_death(philo);
	}
	return ((void *)1);
}
