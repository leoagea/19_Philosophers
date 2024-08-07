/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea < lagea@student.s19.be >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:25:35 by lagea             #+#    #+#             */
/*   Updated: 2024/08/08 00:56:22 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h> //struct timeval
# include <unistd.h>   //sleep
# include <stdlib.h>
# include <stdatomic.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int             dead; // 0 if no dead philo, 1 if 1 one philo just died
	atomic_long		last_eat;
	pthread_mutex_t	eat;
	pthread_mutex_t	print;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	size_t			start_time;
	pthread_t		thread;
}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				nb_must_eat;
	int				all_eaten;
	pthread_mutex_t	dead;
	pthread_mutex_t	*fork;
	t_philo			*philos;
}					t_data;

/*--------------------------------Main---------------------------------*/

size_t              get_current_time(void);

/*-------------------------------Parsing-------------------------------*/

int					parse_arg(t_data *data, char **av);
int init_philo(t_data *data);
int init_fork(t_data *data);

/*--------------------------------Utils--------------------------------*/

int					ft_isdigit(int c);
int					ft_atoi(const char *str);
void                precise_usleep(long usec);
size_t				get_current_time(void);

/*-------------------------------Utils_2-------------------------------*/

void ft_exit(t_data *data);

#endif