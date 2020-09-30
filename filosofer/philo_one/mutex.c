/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:51:48 by iromero-          #+#    #+#             */
/*   Updated: 2020/02/27 16:10:57 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*monitor(void *philo_v)
{
	t_philo		*philo;

	philo = (t_philo*)philo_v;
	while (1)
	{
		pthread_mutex_lock(&philo->mutex);
		if (!philo->is_eating && (get_time() - philo->last_eat) > philo->state->time_to_die)
		{
			philo->state->died = 1;
			ft_writeme_baby(philo, " is DEATH 👻\n");
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->state->somebody_dead_m);
			return ((void*)0);
		}
		pthread_mutex_unlock(&philo->mutex);
		usleep(1000);
	}
}

int		ft_loop(t_philo *phi)
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

void	*ft_vida(t_philo *phi)
{
	int i;
	pthread_t	tid;

	i = 0;
	phi->last_eat = get_time();
	if (pthread_create(&tid, NULL, &monitor, phi) != 0)
		return ((void*)1);
	pthread_detach(tid);
	while (1)
	{
		phi_think(phi);
		if (phi->state->died)
			break ;
		if (!(ft_loop(phi)))
			break ;
	}
	return ((void*)0);
}

void	init_thread(t_state *std)
{
	pthread_t	tid[std->amount];
	int			i;
	int			err;

	start_hilos(std);
	i = 0;
	while (i < std->amount)
		pthread_mutex_init(&std->forks_m[i++], NULL);
	i = 0;
	while (i < std->amount)
	{
		//std->philos[i].last_eat = get_time();
		err = pthread_create(&tid[i], NULL, (void*)&ft_vida, &std->philos[i]);
		usleep(20);
		i++;
	}
	i = 0;
	while (i < std->amount)
		pthread_join(tid[i++], NULL);
	pthread_join(tid[1], NULL);
}

int		main(int argc, char **argv)
{
	t_state std;

	if (argc < 5 || argc > 6)
		return (exit_error("error: bad arguments\n"));
	if (init(&std, argc, argv))
		return (exit_error("Fatal Error\n"));
	init_thread(&std);
	write(1, "🎮 GAME OVER 🎮 ", 20);
}
