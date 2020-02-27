/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iromero- <iromero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 19:12:59 by iromero-          #+#    #+#             */
/*   Updated: 2020/02/27 16:08:42 by iromero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct		s_philo
{
	int				position;
	int				is_eating;
	uint64_t		limit;
	uint64_t		last_eat;
	int				lfork;
	int				rfork;
	int				eat_count;
	struct s_state	*state;
	pthread_mutex_t	*forks_m;
	pthread_mutex_t	mutex;
	pthread_mutex_t	eat_m;
}					t_philo;

typedef struct		s_state
{
	int				amount;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				must_eat_count;
	int				died;
	t_philo			*philos;
	pthread_mutex_t	*forks_m;
	pthread_mutex_t	write_m;
	pthread_mutex_t	somebody_dead_m;
	int				n_forks;
}					t_state;

int					init(t_state *std, int argc, char **argv);
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *s);
uint64_t			get_time(void);
char				*ft_itoa(uint64_t n);
char				*ft_strjoin(char const *s1, char const *s2);
int					exit_error(char const *str);
void				ft_writeme_baby(t_philo *phi, char *str);
void				phi_eating(t_philo *phi);
void 				phi_sleep(t_philo *phi);
void 				phi_think(t_philo *phi);
void				start_hilos(t_state *std);
#endif