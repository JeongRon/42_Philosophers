/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:05:53 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/31 08:03:20 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}

int	print_condition(t_philo *philo, char *str)
{
	time_t	now;
	time_t	print_time;

	pthread_mutex_lock(&philo->info->print);
	if (philo->info->finish_flag == 1)
	{
		pthread_mutex_unlock(&(philo->info->print));
		return (0);
	}
	now = get_time();
	print_time = now - philo->first_time;
	if (now - philo->start_time > philo->info->life_time)
	{
		pthread_mutex_unlock(&philo->info->print);
		return (0);
	}
	printf("%ld %d %s\n", print_time, philo->id + 1, str);
	pthread_mutex_unlock(&philo->info->print);
	return (1);
}

int	main(int ac, char **av)
{
	t_info	info;
	t_philo	*philo;

	if (input_parsing(ac, av, &info) == 1)
	{
		if (set_philo(&philo, &info) == 1)
			simulate(philo);
	}
	return (0);
}
