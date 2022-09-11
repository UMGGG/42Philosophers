/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:16:06 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/11 21:16:26 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_philo
{
	int				philo_id;
	int				eat_count;
	long long		last_eat_time;
	int				this_pid;
	int				is_eat_all;
	pthread_t		monitor;
	struct s_param	*param;
}				t_philo;

typedef struct s_param
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_num;
	int				is_all_safe;
	long long		start_time;
	t_philo			*philo;
	sem_t			*forks_sem;
	sem_t			*print_sem;
	sem_t			*eat_sem;
	sem_t			*search_fork_sem;
	sem_t			*eat_all;
}				t_param;

/*utils*/
int			check_whitespace(const char *str);
int			ft_atoi(const char *str);
int			ft_error(char *str);
void		ft_print(t_param *param, t_philo *philo, char *str);
void		end_process(int dead, t_param *par);
/*check*/
int			check_argv(int argc, char *argv[]);
int			check_is_num(char *str);
void		*check_eat(void *par);
/*init*/
int			ft_philo_init(int argc, char *argv[], t_param *par);
int			ft_make_philo(t_param *par);
int			ft_make_forks(t_param *param);
/*time*/
long long	ft_get_time(void);
void		ft_wait(t_param *param, int time);
/*start*/
int			ft_start_philo(t_param *par, t_philo *philo);
void		*ft_check_die(void *par);
void		finish_thread(t_param *param);
int			check_eat_num(t_philo *phil);
int			check_eat_time(t_philo *phil);
/*philo*/
void		*do_philo(t_philo *philo);
void		do_think(t_philo *philo, t_param *param);
void		do_sleep(t_philo *philo, t_param *param);
void		do_eat(t_philo *philo, t_param *param);
int			get_fork1(t_philo *philo, t_param *param);
#endif
