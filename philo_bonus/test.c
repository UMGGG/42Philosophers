/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeyjeon <jaeyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 16:34:06 by jaeyjeon          #+#    #+#             */
/*   Updated: 2022/09/09 16:55:50 by jaeyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main()
{
	sem_t	*forks;
	int		i;
	int		j;

	i = 0;
	j = 0;
	forks = sem_open("forks", O_CREAT | O_EXCL, 8);
	if (forks == SEM_FAILED)
		printf("[ERROR]sem open error\n");
	while (j != 8)
	{
		sem_wait(forks);
		printf("sem %d use\n", i);
		i++;
		j++;
	}
	sem_close(forks);
	sem_unlink("forks");
	return (0);
}
