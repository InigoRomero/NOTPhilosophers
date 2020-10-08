/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 15:55:37 by iromero-          #+#    #+#             */
/*   Updated: 2020/10/02 18:48:27 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	phi_eating(t_philo *phi)
{
	if (phi->state->died == 0)
	{
		pthread_mutex_lock(&phi->forks_m[phi->lfork]);
		ft_writeme_baby(phi, " has taken a fork 🍴\n");
		pthread_mutex_lock(&phi->forks_m[phi->rfork]);
		ft_writeme_baby(phi, " has taken a fork 🍴\n");
		ft_writeme_baby(phi, " is eating 🍔\n");
		phi->is_eating = 1;
		phi->last_eat = get_time();
		usleep(phi->state->time_to_eat * 1000);
		phi->eat_count++;
		pthread_mutex_unlock(&phi->forks_m[phi->rfork]);
		pthread_mutex_unlock(&phi->forks_m[phi->lfork]);
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	dest = (char*)malloc(sizeof(char *) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	while (*s1 != '\0')
		dest[i++] = *s1++;
	while (*s2 != '\0')
		dest[i++] = *s2++;
	dest[i] = '\0';
	return (dest);
}
