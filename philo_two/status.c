/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:55:37 by iromero-          #+#    #+#             */
/*   Updated: 2020/10/05 17:13:31 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	phi_eating(t_philo *phi)
{
	if (phi->state->died == 0)
	{
		sem_wait(phi->forks_m);
		sem_wait(phi->forks_m);
		phi->is_eating = 1;
		phi->last_eat = get_time();
		ft_writeme_baby(phi, " has taken a fork 🍴\n");
		ft_writeme_baby(phi, " has taken a fork 🍴\n");
		ft_writeme_baby(phi, " is eating 🍔\n");
		usleep(phi->state->time_to_eat * 1000);
		sem_post(phi->forks_m);
		sem_post(phi->forks_m);
		phi->eat_count++;
		phi->is_eating = 0;
	}
}

void	phi_sleep(t_philo *phi)
{
	if (phi->state->died == 0)
	{
		ft_writeme_baby(phi, " is sleeping 🛌\n");
		usleep(phi->state->time_to_sleep * 1000);
	}
}

void	phi_think(t_philo *phi)
{
	if (phi->state->died == 0)
	{
		ft_writeme_baby(phi, " is thinking 🤔\n");
		phi->is_eating = 0;
	}
}
