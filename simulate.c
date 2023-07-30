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

void	*run_thread(void *arg)
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

void	philo_finish_check(t_info *info, t_philo *philo)
{
	int		i;
	time_t	philo_life_time;

	while (1)
	{
		if (info->finish_flag == 1)
			return ;
		if (info->option_cnt > 0)
		{
			i = -1;
			while (++i < info->philo_cnt)
			{
				if (philo[i].option_finish == 0 && \
					philo[i].eat_cnt == info->option_cnt)
				{
					philo[i].option_finish = 1;
					info->option_finish_cnt++;
				}
				if (info->option_finish_cnt == info->philo_cnt)
					return ;
			}
		}
		i = -1;
		while (++i < info->philo_cnt)
		{
			philo_life_time = get_time() - philo[i].first_time;
			if (philo_life_time > info->life_time)
			{
				info->finish_flag = 1;
				printf("%ld %d %s\n", philo_life_time, philo->id + 1, "died\n");
				return ;
			}
		}
	}
}

int	simulate(t_info *info, t_philo *philo)
{
	int			i;
	time_t		now_time;

	i = -1;
	while (++i < info->philo_cnt)
	{
		now_time = get_time();
		philo[i].first_time = now_time;
		philo[i].start_time = now_time;
		if (pthread_create(&(philo[i].thread), NULL, run_thread, &(philo[i])))
			return (ft_error("[Thread] Creat Error\n"));
	}
	philo_finish_check(info, philo);
	i = -1;
	while (++i < info->philo_cnt)
		pthread_join(philo[i].thread, NULL);
	return (1);
}
