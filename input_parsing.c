/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 17:13:05 by jeongrol          #+#    #+#             */
/*   Updated: 2023/07/29 19:13:39 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_av(char *str)
{
	int			i;
	long long	result;

	// 문자열 규격 (첫 문자 '+' 제외 모두 숫자 문자 && [음수,0,int범위 초과] 에러)
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

int	set_mutex_fork(t_info *info)
{
	int	cnt;
	int	i;

	cnt = info->philo_cnt;
	info->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * cnt);
	if (!info->fork)
		return (0);
	i = 0;
	while (i < info->philo_cnt)
	{
		if (pthread_mutex_init(&(info->fork[i]), NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	input_parsing(int ac, char **av, t_info *info)
{
	// 무조건 ac = 5, 6
	if (ac < 5 || 6 < ac)
		return (ft_error("[Count] Argument Error\n"));
	// 입력 av => int형 범위 양수인지 체크 => info 구조체에 넣기 
	info->philo_cnt = check_av(av[1]);
	info->life_time = check_av(av[2]);
	info->eat_time = check_av(av[3]);
	info->sleep_time = check_av(av[4]);
	info->option_cnt = -1;
	if (info->philo_cnt == 0 || info->life_time == 0
		|| info->eat_time == 0 || info->sleep_time == 0
		|| info->option_cnt == 0)
		return (ft_error("[Invalid] Argument Error\n"));
	if (ac == 6)
	{
		info->option_cnt = check_av(av[5]);
		if (info->option_cnt == 0)
			return (ft_error("[Invalid] Argument Error\n"));
	}
	if (set_mutex_fork(&info) == 0)
		return (ft_error("[Set] Mutex Fork Error\n"));
	return (1);
}
