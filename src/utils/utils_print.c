/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 19:37:38 by rbicanic          #+#    #+#             */
/*   Updated: 2022/04/15 19:28:18 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long int	print_relative_time(void)
{
	static int				start = 0;
	static struct timeval	start_time;
	struct timeval			current_time;
	long int				milli_time;

	if (start == 0)
	{
		gettimeofday(&start_time, NULL);
		start = 1;
	}
	gettimeofday(&current_time, NULL);
	milli_time = ((current_time.tv_sec) * 1000 + (current_time.tv_usec) / 1000)
		- ((start_time.tv_sec) * 1000 + (start_time.tv_usec) / 1000);
	return (milli_time);
}

uint8_t	ft_print_messages(t_philo *philo, char *msg, char *color, int death)
{
	(void)color;
	check_death(philo);
	pthread_mutex_lock(philo->print_mutex);
	if ((!death && philo_is_dead(philo)) || philo->nbr_of_meals == 0)
	{
		pthread_mutex_unlock(philo->print_mutex);
		return (1);
	}
	// printf("%s%ld %d %s"RESET, color, print_relative_time(),
	// 	philo->philo_id + 1, msg);
	printf("%ld %d %s", print_relative_time(),
		philo->philo_id + 1, msg);
	pthread_mutex_unlock(philo->print_mutex);
	return (0);
}

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

int	die_sleeping(t_philo *philo)
{
	long int		milli_time;
	struct timeval	current_t;
	struct timeval	last_eat_t;

	last_eat_t = philo->last_eat_time;
	gettimeofday(&current_t, NULL);
	milli_time = (current_t.tv_sec) * 1000 + (current_t.tv_usec) / 1000
		+ philo->time_to_sleep
		- (((last_eat_t.tv_sec) * 1000 + (last_eat_t.tv_usec) / 1000));
	if (milli_time > philo->time_to_die)
	{
		milli_time = (current_t.tv_sec) * 1000 + (current_t.tv_usec) / 1000
			- (((last_eat_t.tv_sec) * 1000 + (last_eat_t.tv_usec) / 1000));
		return (philo->time_to_die - milli_time - 1);
	}
	return (philo->time_to_sleep);
}
