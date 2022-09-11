/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 03:21:06 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/10 23:12:38 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_start_philo(t_param *par, t_philo *philo)
{
	int		i;
	int		dead;
	int		status;

	i = -1;
	par->start_time = ft_get_time();
	sem_unlink("eat_all");
	while (++i < par->philo_num)
	{
		if (getpid() == par->monitor_pid)
			par->philo[i].this_pid = fork();
		if (getpid() != par->monitor_pid)
		{
			do_philo(&philo[i]);
			break ;
		}
	}
	sem_unlink("eat_all");
	while (1)
	{
		dead = waitpid(-1, &status, 0);
		if (dead > 0)
			break ;
	}
	end_process(dead, par);
	finish_thread(par);
	return (0);
}

void	*ft_check_die(void *phil)
{
	t_param	*par;
	t_philo	*philo;

	philo = (t_philo *)phil;
	par = philo->param;
	ft_wait(par, par->time_to_eat);
	while (par->is_all_safe)
	{
		sem_wait(par->eat_sem);
		if (check_eat_time(philo))
			break ;
		if (par->must_eat_num != -1)
			if (check_eat_num(philo))
				break ;
		sem_post(par->eat_sem);
		usleep(100);
	}
	sem_post(par->eat_sem);
	exit(0);
}

int	check_eat_time(t_philo *phil)
{
	long long	time;
	t_param		*p;

	p = phil->param;
	time = ft_get_time() - p->start_time;
	if ((time - phil->last_eat_time) > p->time_to_die)
	{
		sem_wait(p->print_sem);
		p->is_all_safe = 0;
		time = ft_get_time() - p->start_time;
		printf("%lldms	%d	is died\n", time, phil->philo_id);
		return (1);
	}
	return (0);
}

int	check_eat_num(t_philo *phil)
{
	t_param		*p;
	long long	time;

	p = phil->param;
	if (phil->eat_count >= p->must_eat_num && p->must_eat_num != -1 \
	&& phil->is_eat_all == 0)
	{
		printf("sem_post %d\n", phil->philo_id);
		phil->is_eat_all = 1;
	}
	if (phil->is_eat_all == 1)
	{
		if (sem_open("eat_all", O_CREAT | O_EXCL, 0644, 1) == SEM_FAILED)
			return (0);
		else
		{
			p->is_all_safe = 0;
			sem_wait(p->print_sem);
			time = ft_get_time() - p->start_time;
			printf("%lldms	all philo eat %d time\n", time, p->must_eat_num);
			return (1);
		}
	}
	return (0);
}

void	finish_thread(t_param *param)
{
	int	i;

	i = 0;
	while (i < param->philo_num)
	{
		pthread_detach(param->philo[i].monitor);
		i++;
	}
	sem_close(param->eat_sem);
	sem_close(param->print_sem);
	sem_close(param->search_fork_sem);
	sem_close(param->forks_sem);
	sem_close(param->eat_all);
	sem_unlink("eat");
	sem_unlink("print");
	sem_unlink("search");
	sem_unlink("forks");
	sem_unlink("eat_all");
}
