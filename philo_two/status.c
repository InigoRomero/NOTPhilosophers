/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:55:37 by iromero-          #+#    #+#             */
/*   Updated: 2020/03/10 12:31:45 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	phi_eating(t_philo *phi)
{
	/*if ((get_time() - phi->last_eat) > phi->state->time_to_die)
	{
		ft_writeme_baby(phi, " is DEATH 👻\n");
		phi->state->died = 1;
	}
	else*/ if (phi->state->died == 0)
	{
		sem_wait(&phi->forks_m[phi->lfork]);
		ft_writeme_baby(phi, " has taken a fork 🍴\n");
		sem_wait(&phi->forks_m[phi->rfork]);
		ft_writeme_baby(phi, " has taken a fork 🍴\n");
		ft_writeme_baby(phi, " is eating 🍔\n");
		phi->is_eating = 1;
		phi->eat_count++;
		phi->last_eat = get_time();
		usleep(phi->state->time_to_eat * 1000);
		sem_post(&phi->forks_m[phi->rfork]);
		sem_post(&phi->forks_m[phi->lfork]);
		phi->is_eating = 0;
	}

}

void	phi_sleep(t_philo *phi)
{
/*	if ((get_time() - phi->last_eat) > phi->state->time_to_die)
	{
		ft_writeme_baby(phi, " is DEATH 👻\n");
		phi->state->died = 1;
	}
	else */if (phi->state->died == 0)
	{
		ft_writeme_baby(phi, " is sleeping 🛌\n");
		usleep(phi->state->time_to_sleep * 1000);
	}
}

void	phi_think(t_philo *phi)
{
	/*if ((get_time() - phi->last_eat) > phi->state->time_to_die)
	{
		ft_writeme_baby(phi, " is DEATH 👻\n");
		phi->state->died = 1;
	}
	else */if (phi->state->died == 0)
	{
		ft_writeme_baby(phi, " is thinking 🤔\n");
		phi->is_eating = 0;
	}
}
