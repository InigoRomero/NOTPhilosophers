/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:51:48 by iromero-          #+#    #+#             */
/*   Updated: 2020/10/15 18:13:09 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int			ft_loop(t_philo *phi)
{
	if (phi->state->died)
		return (0);
	phi_eating(phi);
	if (phi->state->died)
		return (0);
	phi_sleep(phi);
	if (phi->state->died)
		return (0);
	return (1);
}

static void	*monitor(void *philo_v)
{
	t_philo		*philo;

	philo = (t_philo*)philo_v;
	while (1)
	{
		sem_wait(philo->monitor);
		if ((get_time() - philo->last_eat) > philo->state->time_to_die
			&& !philo->is_eating)
		{
			if (philo->state->died == 0)
			{
				sem_post(philo->state->died2);
				ft_writeme_baby2(philo, " is DEATH 👻\n");
			}
			sem_post(philo->monitor);
			return ((void*)0);
		}
		if (philo->state->died || (philo->state->must_eat_count
			&& philo->eat_count == philo->state->must_eat_count))
			break ;
		sem_post(philo->monitor);
		usleep(100);
	}
	sem_close(philo->monitor);
	return ((void*)0);
}

void		*ft_vida(t_philo *phi)
{
	pthread_t	tid;

	phi->last_eat = get_time();
	if (pthread_create(&tid, NULL, &monitor, phi) != 0)
		return ((void*)1);
	while (1)
	{
		if (phi->state->died || (phi->state->must_eat_count
			&& phi->eat_count == phi->state->must_eat_count))
			break ;
		phi_think(phi);
		if (phi->state->died || (phi->state->must_eat_count
			&& phi->eat_count == phi->state->must_eat_count))
			break ;
		if (!(ft_loop(phi)) || (phi->state->must_eat_count
			&& phi->eat_count == phi->state->must_eat_count))
			break ;
	}
	return ((void*)0);
}

void		init_thread(t_state *std)
{
	int		i;

	start_hilos(std);
	i = -1;
	while (i++ < std->amount)
	{
		std->philos[i].pid = fork();
		if (std->philos[i].pid < 0)
			return ;
		else if (std->philos[i].pid == 0)
		{
			ft_vida(&std->philos[i]);
			exit(0);
		}
		usleep(100);
	}
	ft_check_exit(std);
}

int			main(int argc, char **argv)
{
	t_state std;
	int		i;

	if (argc < 5 || argc > 6)
		return (exit_error("error: bad arguments\n"));
	std.died = 0;
	if (init(&std, argc, argv))
		return (exit_error("Fatal Error\n"));
	std.init = get_time();
	init_thread(&std);
	i = 0;
	while (i < std.amount)
		kill(std.philos[i++].pid, SIGKILL);
	clear_state(&std);
}
