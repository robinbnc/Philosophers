/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:59:05 by rbicanic          #+#    #+#             */
/*   Updated: 2022/04/04 17:23:10 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdint.h>

# define RED     "\x1b[31;1m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

# define OVER_INT_MSG "Error: you should past an int as argument\n"
# define ONE_PHILO_MSG "Error: you should have at least 1 philo\n"
# define ALLOC_ERR_MSG "Error: allocation error\n"
# define EMPTY_ARG_MSG "Error: Arguments should not be empty\n"
# define NUMERIC_ARG_MSG "Error: Arguments should be numeric\n"
# define ARG_NBR_MSG "Error: Invalid number of arguments\n"
# define CREATE_THREAD_MSG "Error: Failed to create thread\n"
# define JOIN_THREAD_MSG "Error: Failed to join thread\n"

# define EATING_MSG "is eating\n"
# define SLEEPING_MSG "is sleeping\n"
# define THINKING_MSG "is thinking\n"
# define DEATH_MSG "died\n"
# define FORK_MSG "has taken a fork\n"

typedef struct s_philo
{
	int				philo_id;
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_of_meals;
	struct timeval	last_eat_time;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*left_forks_mutex;
	int				*left_forks;
	pthread_mutex_t	*right_forks_mutex;
	int				*right_forks;
	pthread_mutex_t	*dead_mutex;
	int				*dead;
}				t_philo;

typedef struct s_table
{
	int				philo_nbr;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*dead_mutex;
	int				*dead;
	pthread_mutex_t	*forks_mutex;
	int				*forks;
	t_philo			*philos;
}				t_table;

/*
** parsing
*/

uint8_t		argument_are_valid(int ac, char *av[]);
t_table		*initialize_table(t_table *table, char *av[]);
void		initialize_mutex(t_table *table);
void		destroy_mutex(t_table *table);
uint8_t		initialize_data(t_table *table, char *av[]);

/*
** Utils
*/

int			ft_atoi(const char *nptr);
void		free_table(t_table *table);
int			ft_strlen(char *str);
int			is_over_max(const char *nptr, int sign);
uint8_t		ft_malloc(void **ptr, size_t size);
void		ft_print_messages(t_philo *philo, char *msg, char *color);
long int	print_relative_time(void);

/*
** exec
*/

uint8_t		initialize_threads(t_table *table);
void		*routine(void *arg);
uint8_t		philo_is_dead(t_philo *philo);

#endif
