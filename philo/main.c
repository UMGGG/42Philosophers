/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:21:02 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/11 21:11:08 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_param	param;

	if (argc != 5 && argc != 6)
		return (ft_error("[Error]check num of arg"));
	if (check_argv(argc, argv))
		return (ft_error("[Error]check argv data"));
	if (ft_philo_init(argc, argv, &param))
		return (1);
	if (ft_start_philo(&param, (&param)->philo))
		return (1);
	return (0);
}
