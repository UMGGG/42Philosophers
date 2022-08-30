/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 03:21:06 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/08/31 04:18:34 by jaeyjeon         ###   ########.fr       */
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
	if (ft_check_die(par))
		return (1);
	return (0);
}

int	ft_check_die(t_param *par)
{
	while (1)
	{
		if (!(par->is_all_safe))
			return (1);
	}
}
