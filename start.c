/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 03:21:06 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/01 05:49:59 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_start_philo(t_param *par, t_philo *philo)
{
	int		i;
	void	*philo_v;

	i = 0;
	par->start_time = ft_get_time();
	while (i < par->philo_num)
	{
		philo_v = (void *)&(philo[i]);
		if (pthread_create(&(philo[i].tid), NULL, do_philo, philo_v) == -1)
			return (ft_error("[Error]thread create fail"));
		i++;
	}
	ft_check_die(par);
	return (0);
}

int	ft_check_die(t_param *par)
{
	int			i;
	long long	time;

	i = 0;
	usleep(par->time_to_die * 1000);
	while (par->is_all_safe)
	{
		while (i < par->philo_num)
		{
			time = ft_get_time() - par->start_time;
			if ((time - par->philo[i].last_eat_time) > par->time_to_die)
			{
				par->is_all_safe = 0;
				printf("%lldms	%d	is died\n", time, par->philo[i].philo_id);
				break ;
			}
			usleep(1);
			i++;
		}
		i = 0;
	}
	return (0);
}
