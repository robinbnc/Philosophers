/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:33:14 by rbicanic          #+#    #+#             */
/*   Updated: 2022/04/03 16:15:47 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	print_forks(t_table *table)
{
	// int	i;

	// i = 0;
	printf(MAGENTA"forks ptr %p: "RESET, table->forks);
	// while (i < table->philo_nbr)
	// {
	// 	printf("%d ", table->forks[i]);
	// 	i++;
	// }
	printf("\n\n");
}

void	print_philo_data(t_table *table)
{
	int	i;

	i = 0;
	while (table->philos[i].philo_id >= 0)
	{
		printf(BLUE "Philo id %d:\n" RESET, table->philos[i].philo_id);
		printf(GREEN "\ttime_to_die: %d\n", table->philos[i].time_to_die);
		printf("\ttime_to_eat: %d\n", table->philos[i].time_to_eat);
		printf("\ttime_to_sleep: %d\n", table->philos[i].time_to_sleep);
		printf("\tnbr_of_meals: %d\n", table->philos[i].nbr_of_meals);
		printf(YELLOW "\tPhilo nbr %d:\n" RESET, table->philos[i].philo_nbr);
		printf(RED "\tdead ptr %p\n"RESET, table->philos[i].dead);
		printf(MAGENTA "\tforks ptr: %p\n\n" RESET, table->philos[i].left_forks);
		i++;
	}
	printf("\n\n");
}

void	print_data(t_table *table)
{
	printf(YELLOW "philo_nbr: %d\n\n", table->philo_nbr);
	printf(RED "dead ptr %p\n\n"RESET, table->dead);
	print_forks(table);
	print_philo_data(table);
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (!argument_are_valid(argc, argv))
		return (0);
	if (initialize_data(&table, &argv[1]))
		return (1);
	// print_data(&table);
	free_table(&table);
	return (0);
}
