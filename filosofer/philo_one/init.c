/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:19:05 by iromero-          #+#    #+#             */
/*   Updated: 2020/02/27 16:09:04 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_semaphores(t_state *state)
{
	if ((state->forks_m = ft_sem_open(SEMAPHORE_FORK, state->amount)) < 0
		|| (state->write_m = ft_sem_open(SEMAPHORE_WRITE, 1)) < 0
		|| (state->somebody_dead_m = ft_sem_open(SEMAPHORE_DEAD, 0)) < 0)
		return (1);
	return (0);
}

int			init(t_state *std, int argc, char **argv)
{
	std->amount = ft_atoi(argv[1]);
	std->time_to_die = ft_atoi(argv[2]);
	std->time_to_eat = ft_atoi(argv[3]);
	std->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		std->must_eat_count = ft_atoi(argv[5]);
	else
		std->must_eat_count = 0;
	if (std->amount < 2 || std->amount > 200 || std->time_to_die < 60
		|| std->time_to_eat < 60 || std->time_to_sleep < 60
		|| std->must_eat_count < 0)
		return (1);
	return (0);
}

void	start_hilos(t_state *std)
{
	int i;

	i = 0;
	if (!(std->philos =
		(t_philo*)malloc(sizeof(*(std->philos)) * std->amount)))
		return ;
	if (!(std->forks_m = (pthread_mutex_t*)
		malloc(sizeof(*(std->forks_m)) * std->amount)))
		return ;
	std->died = 0;
	while (i < std->amount)
	{
		std->philos[i].is_eating = 0;
		std->philos[i].position = i;
		std->philos[i].lfork = i;
		std->philos[i].rfork = (i + 1) % std->amount;
		std->philos[i].eat_count = 0;
		std->philos[i].state = std;
		std->philos[i].forks_m = std->forks_m;
		i++;
	}
}
