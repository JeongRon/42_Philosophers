/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:05:53 by jeongrol          #+#    #+#             */
/*   Updated: 2023/08/14 22:07:58 by jeongrol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_info	info;
	t_philo	*philo;

	if (set_info(ac, av, &info) == 1)
	{
		if (set_philo(&philo, &info) == 1)
		{
			if (info.philo_cnt == 1)
				simulate(philo);
			else
				simulate(philo);
		}
	}
	return (0);
}
