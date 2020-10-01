/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 13:55:41 by iromero-          #+#    #+#             */
/*   Updated: 2020/10/01 17:21:19 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
 
sem_t	*ft_sem_open(char const *name, int value)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}

char	*make_semaphore_name(char const *base, char *buffer, int position)
{
	int	i;

	i = ft_strcpy(buffer, base);
	while (position > 0)
	{
		buffer[i++] = (position % 10) + '0';
		position /= 10;
	}
	buffer[i] = 0;
	return (buffer);
}

int		clear_state(t_state *state)
{
	int		i;
	char	semaphore[255];

	sem_unlink("mutex");
	if (state->philos)
	{
		i = 0;
		while (i < state->amount)
		{
			make_semaphore_name("semaforoeat", (char*)semaphore, i++);
			sem_unlink(semaphore);
		}
		free(state->philos);
	}
	return (1);
}