/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 22:48:51 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/31 08:11:27 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	simulate_finish_check(t_philo *philo)
{
	time_t	philo_life_time;

	if (philo->info->option_cnt > 0)
	{

		if (philo->option_finish == 0 && \
			philo->eat_cnt == philo->info->option_cnt)
		{
			philo->option_finish = 1;
			philo->info->option_finish_cnt++;
		}
		if (philo->info->option_finish_cnt == philo->info->philo_cnt)
		{
			philo->info->finish_flag = 1;
			return (1);
		}
	}
	philo_life_time = get_time() - philo->start_time;
	if (philo_life_time > philo->info->life_time)
	{
		print_condition(philo, "died");
		return (1);
	}
	return (0);
}

static void	*run_thread(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if ((philo->id + 1) % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (take_fork(philo) == 0)
			break ;
		if (eating(philo) == 0)
			break ;
		if (sleeping(philo) == 0)
			break ;
		if (thinking(philo) == 0)
			break ;
	}
	return (NULL);
}

int	simulate(t_philo *philo)
{
	int			i;
	time_t		now_time;

	i = -1;
	now_time = get_time();
	while (++i < philo->info->philo_cnt)
	{
		philo[i].first_time = now_time;
		philo[i].start_time = now_time;
		if (pthread_create(&philo[i].thread, NULL, run_thread, &philo[i]))
			return (ft_error("[Thread] Creat Error\n"));
	}
	i = 0;
	while (1)
	{
		if (simulate_finish_check(&philo[i]) == 1)
			break ;
		i = (i + 1) % philo->info->philo_cnt;
	}
	i = -1;
	while (++i < philo->info->philo_cnt)
		pthread_join(philo[i].thread, NULL);
	return (1);
}
