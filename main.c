/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongrol <jeongrol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 18:05:53 by jeongrol          #+#    #+#             */
/*   Updated: 2023/08/07 16:42:11 by jeongrol         ###   ########.fr       */
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
			simulate(philo);
	}
	return (0);
}

// 42 헤더 변경 (집에서 변경 불가)
// Norm 체크