/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:13:05 by jeongrol          #+#    #+#             */
/*   Updated: 2023/08/13 18:31:15 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_av(char *str)
{
	int			i;
	long long	result;

	i = 0;
	if (str[i] == '+')
		i++;
	result = 0;
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9')
		{
			result = result * 10 + (str[i] - '0');
			if (result > 2147483647)
				return (0);
			i++;
		}
		else
			return (0);
	}
	if (result == 0)
		return (0);
	return ((int)result);
}

static int	set_mutex(t_info *info)
{
	int	cnt;
	int	i;

	cnt = info->philo_cnt;
	info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * cnt);
	if (!info->fork)
		return (0);
	i = -1;
	while (++i < info->philo_cnt)
	{
		if (pthread_mutex_init(&(info->fork[i]), NULL) != 0)
			return (0);
	}
	if (pthread_mutex_init(&(info->start), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(info->print), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(info->time), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(info->eat), NULL) != 0)
		return (0);
	return (1);
}

static int	set_fork_state(t_info *info)
{
	int	cnt;
	int	i;

	cnt = info->philo_cnt;
	info->fork_state = (int *)malloc(sizeof(int) * cnt);
	if (!info->fork_state)
		return (0);
	i = -1;
	while (++i < info->philo_cnt)
		info->fork_state[i] = 0;
	return (1);
}

int	set_info(int ac, char **av, t_info *info)
{
	if (ac < 5 || 6 < ac)
		return (ft_error("[Count] Argument Error\n"));
	info->philo_cnt = check_av(av[1]);
	info->life_time = check_av(av[2]);
	info->eat_time = check_av(av[3]);
	info->sleep_time = check_av(av[4]);
	info->option_cnt = -1;
	info->option_finish_cnt = 0;
	info->finish_flag = 0;
	if (info->philo_cnt == 0 || info->life_time == 0
		|| info->eat_time == 0 || info->sleep_time == 0)
		return (ft_error("[Invalid] Argument Error\n"));
	if (ac == 6)
	{
		info->option_cnt = check_av(av[5]);
		if (info->option_cnt == 0)
			return (ft_error("[Invalid] Argument Error\n"));
	}
	info->first_time = 0;
	if (set_mutex(info) == 0)
		return (ft_error("[Set] Mutex Error\n"));
	if (set_fork_state(info) == 0)
		return (ft_error("[Set] Allocated fork Error\n"));
	return (1);
}
