/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:51:48 by iromero-          #+#    #+#             */
/*   Updated: 2020/02/26 12:35:26 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_t tid[5];
int counter;
pthread_mutex_t lock;

int	exit_error(char const *str)
{
	if (str)
		write(1, str, ft_strlen(str));
	return (1);
}

void* doSomeThing(void *arg)
{
    pthread_mutex_lock(&lock);

    int i = 0;
    counter += 1;
    printf("\n Job %d started\n", counter);

    for(i=0; i<1000;i++);

    printf("\n Job %d finished i = %d\n", counter, i);

    pthread_mutex_unlock(&lock);

    return NULL;
}

static void	init_thread(t_state *std)
{
	pthread_t hilo;
	int i = 0, err;
	
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return ;
    }
	while(i < 5)
    {
		std->start = get_time();
        err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
		usleep(100);
        if (err != 0)
            printf("\ncan't create thread");
		printf("started at: %llu", std->start);
        i++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_mutex_destroy(&lock);
}

int main(int argc, char **argv)
{
	t_state std;

	if (argc < 5 || argc > 6)
		return (exit_error("error: bad arguments\n"));
	if (init(&std, argc, argv))
		return (exit_error("Fatal Error\n"));
	init_thread(&std);
}

