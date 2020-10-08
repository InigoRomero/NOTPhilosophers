/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:19:05 by iromero-          #+#    #+#             */
/*   Updated: 2020/10/06 17:39:46 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		init(t_state *std, int argc, char **argv)
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
	int		i;
	char	semaphore[250];

	i = 0;
	if (!(std->philos =
		(t_philo*)malloc(sizeof(*(std->philos)) * std->amount)))
		return ;
	std->mutex = ft_sem_open("mutex", 1);
	std->forks_m = ft_sem_open("SEMAPHORE_FORK", std->amount);
	std->died = 0;
	while (i < std->amount)
	{
		std->philos[i].is_eating = 0;
		std->philos[i].position = i;
		make_semaphore_name("semaforo", (char*)semaphore, i);
		std->philos[i].monitor = ft_sem_open(semaphore, i);
		std->philos[i].lfork = i;
		std->philos[i].eat_count = 0;
		std->philos[i].rfork = (i + 1) % std->amount;
		std->philos[i].eat_count = 0;
		std->philos[i].state = std;
		std->philos[i].forks_m = std->forks_m;
		i++;
	}
}
