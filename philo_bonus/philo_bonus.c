/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 03:20:44 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/09 17:48:48 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*do_philo(void *philo)
{
	t_philo	*phil;
	t_param	*param;

	phil = (t_philo *)philo;
	param = phil->param;
	if (phil->philo_id % 2 != 1)
		ft_wait(param, 1);
	while (param->is_all_safe)
	{
		while (get_fork1(phil, param))
			usleep(100);
		do_sleep(phil, param);
		do_think(phil, param);
		usleep(100);
	}
	return (0);
}

int	get_fork1(t_philo *p, t_param *param)
{
	if (param->is_all_safe == 0)
		return (0);
	sem_wait(param->search_fork_sem);
	if (param->left_fork >= 2)
	{
		sem_wait(param->forks_sem);
		ft_print(param, p, "has taken a fork");
		param->left_fork -= 1;
		sem_wait(param->forks_sem);
		ft_print(param, p, "has taken a fork");
		param->left_fork -= 1;
		do_eat(p, param);
		sem_post(param->search_fork_sem);
		ft_wait(param, param->time_to_eat);
		sem_post(param->forks_sem);
		sem_post(param->forks_sem);
		param->left_fork += 2;
		p->eat_count++;
		return (0);
	}
	sem_post(param->search_fork_sem);
	return (1);
}

void	do_think(t_philo *philo, t_param *param)
{
	if (param->is_all_safe == 0)
		param->is_all_safe = 0;
	else
	{
		ft_print(param, philo, "is thinking");
	}
}

void	do_sleep(t_philo *philo, t_param *param)
{
	if (param->is_all_safe == 0)
		param->is_all_safe = 0;
	else
	{
		ft_print(param, philo, "is sleeping");
		ft_wait(param, param->time_to_sleep);
	}
}

void	do_eat(t_philo *philo, t_param *param)
{
	long long	time;

	if (param->is_all_safe == 0)
		time = 0;
	else
	{
		sem_wait(param->eat_sem);
		time = ft_get_time() - param->start_time;
		philo->last_eat_time = time;
		ft_print(param, philo, "is eating");
		sem_post(param->eat_sem);
	}
}
