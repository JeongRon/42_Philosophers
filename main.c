/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:05:53 by jeongrol          #+#    #+#             */
/*   Updated: 2023/08/15 17:45:23 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_all(t_philo *philo, t_info *info)
{
	int		i;

	free(philo);
	free(info->fork_state);
	i = -1;
	while (++i < info->philo_cnt)
		pthread_mutex_destroy(&(info->fork[i]));
	pthread_mutex_destroy(&(info->start));
	pthread_mutex_destroy(&(info->print));
	pthread_mutex_destroy(&(info->time));
	pthread_mutex_destroy(&(info->eat));
	free(info->fork);
}

int	main(int ac, char **av)
{
	t_info	info;
	t_philo	*philo;

	info.fork = NULL;
	info.fork_state = NULL;
	philo = NULL;
	if (set_info(ac, av, &info) == 1)
		if (set_philo(&philo, &info) == 1)
			simulate(philo);
	free_all(philo, &info);
	return (0);
}
