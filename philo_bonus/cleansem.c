/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleansem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 16:34:06 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/09 21:22:35 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(void)
{
	sem_unlink("forks");
	sem_unlink("eat");
	sem_unlink("print");
	sem_unlink("search");
	sem_unlink("eat_all");
	return (0);
}
