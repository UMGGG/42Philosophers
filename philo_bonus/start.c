/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 03:21:06 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/09 17:17:53 by jaeyjeon         ###   ########.fr       */
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
	ft_wait(par, par->time_to_eat);
	ft_check_die(par);
	return (0);
}

void	ft_check_die(t_param *par)
{
	while (par->is_all_safe)
	{
		sem_wait(par->eat_sem);
		if (check_eat_time(par))
			break ;
		if (par->must_eat_num != -1)
			if (check_eat_num(par))
				break ;
		sem_post(par->eat_sem);
		usleep(100);
	}
	sem_post(par->eat_sem);
	finish_thread(par);
}

int	check_eat_time(t_param *p)
{
	long long	time;
	int			i;

	i = 0;
	while (i < p->philo_num)
	{
		time = ft_get_time() - p->start_time;
		if ((time - p->philo[i].last_eat_time) > p->time_to_die)
		{
			sem_wait(p->print_sem);
			p->is_all_safe = 0;
			printf("%lldms	%d	is died\n", time, p->philo[i].philo_id);
			sem_post(p->print_sem);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_eat_num(t_param *p)
{
	long long	time;
	int			i;
	int			check;

	i = 0;
	check = 0;
	while (i < p->philo_num)
	{
		if (p->philo[i].eat_count >= p->must_eat_num && p->must_eat_num != -1)
			check++;
		i++;
	}
	if (check == p->philo_num)
	{
		sem_wait(p->print_sem);
		p->is_all_safe = 0;
		time = ft_get_time() - p->start_time;
		printf("%lldms	all philo eat %d time\n", time, p->must_eat_num);
		sem_post(p->print_sem);
		return (1);
	}
	return (0);
}

void	finish_thread(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->philo_num)
	{
		pthread_join(param->philo[i].tid, NULL);
		i++;
	}
	i = 0;
	sem_close(param->eat_sem);
	sem_close(param->print_sem);
	sem_close(param->search_fork_sem);
	sem_close(param->forks_sem);
	sem_unlink("eat");
	sem_unlink("print");
	sem_unlink("search");
	sem_unlink("forks");
}
