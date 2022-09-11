/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:35:37 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/10 23:09:59 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_philo_init(int argc, char *argv[], t_param *par)
{
	if (check_argv(argc, argv))
		return (ft_error("[Error]check argv data"));
	par->philo_num = ft_atoi(argv[1]);
	par->time_to_die = ft_atoi(argv[2]);
	par->time_to_eat = ft_atoi(argv[3]);
	par->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		par->must_eat_num = ft_atoi(argv[5]);
	else
		par->must_eat_num = -1;
	if (par->must_eat_num == 0)
		return (ft_error("0ms	all philo eat 0 time"));
	par->is_all_safe = 1;
	par->left_fork = par->philo_num;
	par->monitor_pid = getpid();
	if (par->philo_num == 1)
		par->left_fork = 2;
	if (ft_make_philo(par))
		return (ft_error("[Error]malloc philo fail"));
	if (ft_make_forks(par))
		return (1);
	return (0);
}

int	ft_make_philo(t_param *par)
{
	int		i;

	i = 0;
	par->philo = malloc(sizeof(t_param) * (par->philo_num));
	if (par->philo == NULL)
		return (1);
	while (i < par->philo_num)
	{
		par->philo[i].eat_count = 0;
		par->philo[i].last_eat_time = 0;
		par->philo[i].param = par;
		par->philo[i].philo_id = i + 1;
		par->philo[i].is_eat_all = 0;
		i++;
	}
	return (0);
}

int	ft_make_forks(t_param *p)
{
	int	errno;

	errno = 0;
	p->eat_sem = sem_open("eat", O_CREAT | O_EXCL, 0644, 1);
	if (p->eat_sem == SEM_FAILED)
	{
		printf("%d\n", errno);
		return (ft_error("[Error]eat_sem open fail"));
	}
	p->print_sem = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	if (p->print_sem == SEM_FAILED)
		return (ft_error("[Error]print_sem open fail"));
	p->search_fork_sem = sem_open("search", O_CREAT | O_EXCL, 0644, 1);
	if (p->search_fork_sem == SEM_FAILED)
		return (ft_error("[Error]search_fork_sem open fail"));
	p->forks_sem = sem_open("forks", O_CREAT | O_EXCL, 0644, p->philo_num);
	if (p->search_fork_sem == SEM_FAILED)
		return (ft_error("[Error]forks_sem open fail"));
	p->eat_all = sem_open("eat_all", O_CREAT | O_EXCL, 0644, p->philo_num);
	if (p->eat_all == SEM_FAILED)
		return (ft_error("[Error]eat_all open fail"));
	return (0);
}
