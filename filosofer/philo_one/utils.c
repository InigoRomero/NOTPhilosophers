/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 11:51:05 by iromero-          #+#    #+#             */
/*   Updated: 2020/02/27 16:05:00 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint64_t		get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

static int		longofnum(uint64_t n)
{
	int leng;

	leng = 0;
	if (n < 0)
	{
		leng++;
		n = n * -1;
	}
	while (n > 0)
	{
		n = n / 10;
		leng++;
	}
	return (leng);
}

static char		*inttochar(uint64_t n, char *num, int leng)
{
	num[leng--] = '\0';
	if (n == 0)
		num[0] = 48;
	if (n < 0)
	{
		num[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		num[leng--] = 48 + (n % 10);
		n = n / 10;
	}
	return (num);
}

char			*ft_itoa(uint64_t n)
{
	char	*num;
	int		leng;

	leng = longofnum(n);
	if (!n)
		leng = 1;
	if (!(num = (char *)malloc(sizeof(char) * (leng + 1))))
		return (NULL);
	return (num = inttochar(n, num, leng));
}
