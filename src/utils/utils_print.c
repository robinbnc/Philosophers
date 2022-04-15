/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 19:37:38 by rbicanic          #+#    #+#             */
/*   Updated: 2022/04/15 14:01:16 by rbicanic         ###   ########.fr       */
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

void	ft_print_messages(t_philo *philo, char *msg, char *color, int death)
{
	(void)color;
	pthread_mutex_lock(philo->print_mutex);
	if (!death && philo_is_dead(philo))
	{
		pthread_mutex_unlock(philo->print_mutex);
		return ;
	}
	// printf("%s%ld %d %s"RESET, color, print_relative_time(),
	// 	philo->philo_id + 1, msg);
	printf("%ld %d %s", print_relative_time(),
		philo->philo_id + 1, msg);
	pthread_mutex_unlock(philo->print_mutex);
}
