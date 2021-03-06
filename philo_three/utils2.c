/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:04:26 by iromero-          #+#    #+#             */
/*   Updated: 2020/10/08 17:45:28 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		exit_error(char const *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}

void	ft_writeme_baby(t_philo *phi, char *str)
{
	char *time;
	char *position;
	char *temp;
	char *temp2;

	if (phi->state->died == 0)
	{
		time = ft_itoa(get_time() - phi->state->init);
		position = ft_itoa(phi->position);
		temp = ft_strjoin("\e[1;35m", time);
		free(time);
		temp2 = ft_strjoin(temp, ": \e[1;31mFilósofo ");
		free(temp);
		temp = ft_strjoin(temp2, position);
		free(position);
		free(temp2);
		temp2 = ft_strjoin(temp, str);
		sem_wait(phi->state->mutex);
		write(1, temp2, ft_strlen(temp2));
		free(temp);
		free(temp2);
		sem_post(phi->state->mutex);
	}
}

void	ft_writeme_baby2(t_philo *phi, char *str)
{
	char *time;
	char *position;
	char *temp;
	char *temp2;

	time = ft_itoa(get_time() - phi->state->init);
	position = ft_itoa(phi->position);
	temp = ft_strjoin("\e[1;35m", time);
	free(time);
	temp2 = ft_strjoin(temp, ": \e[1;31mFilósofo ");
	free(temp);
	temp = ft_strjoin(temp2, position);
	free(position);
	free(temp2);
	temp2 = ft_strjoin(temp, str);
	sem_wait(phi->state->mutex);
	write(1, temp2, ft_strlen(temp2));
	free(temp);
	free(temp2);
	sem_post(phi->state->mutex);
	exit(0);
}

size_t	ft_strlen(const char *s)
{
	size_t	value;
	int		i;

	i = 0;
	value = 0;
	while (s[i] != '\0')
	{
		i++;
		value++;
	}
	return (value);
}

int		ft_atoi(const char *str)
{
	int					i;
	unsigned long long	num;
	int					neg;

	neg = 1;
	num = 0;
	i = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] <= '9' && str[i] >= '0')
	{
		if (num > __LONG_LONG_MAX__ || i >= 19)
		{
			if (neg == 1)
				return (-1);
			else
				return (0);
		}
		num = num * 10 + (str[i++] - 48);
	}
	return ((int)num * neg);
}
