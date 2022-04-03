/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 19:37:38 by rbicanic          #+#    #+#             */
/*   Updated: 2022/04/03 23:00:05 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_print_messages(t_philo *philo, char *msg, char *color)
{
	struct timeval	current_time;

	if (!philo_is_dead(philo))
	{
		gettimeofday(&current_time, NULL);// peut etre check retour
		pthread_mutex_lock(philo->print_mutex);
		printf("%s", color);
		printf("%ld ", current_time.tv_usec / 1000);
		printf("%d ", philo->philo_id + 1);
		printf("%s", msg);
		printf(RESET);
		pthread_mutex_unlock(philo->print_mutex);
	}
}