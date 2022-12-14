/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:16:06 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/12 15:59:13 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				philo_id;
	int				leftfork;
	int				rightfork;
	int				eat_count;
	long long		last_eat_time;
	pthread_t		tid;
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
	int				*fork_st;
	long long		start_time;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	eat;
	pthread_mutex_t	search_fork;
}				t_param;

/*utils*/
int			check_whitespace(const char *str);
int			ft_atoi(const char *str);
int			ft_error(char *str);
void		ft_print(t_param *param, t_philo *philo, char *str);
/*check_argv*/
int			check_argv(int argc, char *argv[]);
int			check_is_num(char *str);
/*init*/
int			ft_philo_init(int argc, char *argv[], t_param *par);
int			ft_make_philo(t_param *par);
int			ft_make_forks(t_param *param);
/*time*/
long long	ft_get_time(void);
void		ft_wait(t_param *param, int time);
/*start*/
int			ft_start_philo(t_param *par, t_philo *philo);
void		ft_check_die(t_param *par);
void		finish_thread(t_param *param);
int			check_eat_num(t_param *p);
int			check_eat_time(t_param *p);
/*philo*/
void		*do_philo(void *philo);
void		do_think(t_philo *philo, t_param *param);
void		do_sleep(t_philo *philo, t_param *param);
void		do_eat(t_philo *philo, t_param *param);
int			get_fork(t_philo *philo, t_param *param);
#endif
