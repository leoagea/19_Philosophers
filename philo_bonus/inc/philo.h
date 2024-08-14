/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:25:35 by lagea             #+#    #+#             */
/*   Updated: 2024/08/14 17:05:46 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
#include <semaphore.h>
# include <stdatomic.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h> //struct timeval
# include <unistd.h>   //sleep
#include <fcntl.h>
#include <signal.h>

# define RED "\033[1;31m"   // DIED
# define BLUE "\033[34;01m" // FORK
# define RESET "\033[0m"
# define FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "died"
# define ERR_NB_ARG "Error: Wrong number of arguments"
# define ERR_1 "Error: Input invalid character"
# define ERR_2 "Error: Input invalid values"
# define ERR_SEMA_1 "Error: Open semaphore"
# define ERR_ALLOC_1 "Error: Allocation pthread"
# define ERR_ALLOC_2 "Error: Allocation pid array"
# define ERR_ALLOC_3 "Error: Allocation struct philo"
# define ERR_THREAD "Error: Thread creation"
# define ERR_DETACH "Error: Thread detach"
# define ERR_JOIN "Error: Thread join"
# define ERR_GTOD "Error: gettimeofday() Failure"

struct	s_data;

typedef struct s_philo
{
	int				id;
	int				eat_cont;
	int				status;
	u_int64_t		last_eat;
	pthread_t		t1;
	pthread_mutex_t lock;
	// pthread_mutex_t dead;
	struct s_data	*data;
	
}					t_philo;

typedef struct s_data
{
	int				philo_num;
	int				meals_nb;
	int				*pid;
	t_philo			*philos;
	u_int64_t		death_time;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	u_int64_t		start_time;
	sem_t			*fork;
	sem_t			*write;
}					t_data;

/*---------------------------Action--------------------------*/

void				eat(t_philo *philo);

/*--------------------------Routine--------------------------*/

void process_kill(t_data *data);
void	routine(t_data *data, int i);
int					loop_process(t_data *data);

/*----------------------------Init---------------------------*/

int					init(t_data *data, char **av, int ac);

/*----------------------------Atoi---------------------------*/

int					ft_atoi(const char *str);

/*---------------------------Utils---------------------------*/

void				ft_exit(t_data *data);
int					ft_error(char *str, t_data *data);
int					check_input(char **av);
int					ft_strcmp(char *s1, char *s2);

/*--------------------------Utils_2--------------------------*/

u_int64_t			get_time(void);
int					ft_usleep(useconds_t time);
void				print(char *str, t_philo *philo);
void delete_sema(t_data *data);

#endif