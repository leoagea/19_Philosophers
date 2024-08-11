/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea < lagea@student.s19.be >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:25:35 by lagea             #+#    #+#             */
/*   Updated: 2024/08/12 01:50:14 by lagea            ###   ########.fr       */
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

#define RED "\033[1;31m" //DIED
#define BLUE "\033[34;01m"  //FORK
#define RESET    "\033[0m"
#define FORK "has taken a fork"
#define EATING "is eating"
#define SLEEPING "is sleeping"
#define THINKING "is thinking"
#define DEAD "died"
#define ERR_NB_ARG "Error: Wrong number of arguments"
#define ERR_1 "Error: Input invalid character"
#define ERR_2 "Error: Input invalid values"
#define ERR_ALLOC_1 "Error: Allocation pthread"
#define ERR_ALLOC_2 "Error: Allocation mutex"
#define ERR_ALLOC_3 "Error: Allocation struct philo"
#define ERR_THREAD "Error: Thread creation"
#define ERR_JOIN "Error: Thread join"
#define ERR_GTOD "Error: gettimeofday() Failure"

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		t1;
	int				id;
	int				eat_cont;
	int				status;
	int				eating;
	uint64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

typedef struct s_data
{
	pthread_t		*thread;
	int				philo_num;
	int				meals_nb;
	int				dead;
	int				finished;
	t_philo			*philos;
	u_int64_t		death_time;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	u_int64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	write;
}	t_data;

/*---------------------------Action--------------------------*/

void	eat(t_philo *philo);

/*--------------------------Routine--------------------------*/

void	*routine(void *philo_pointer);
int	loop_thread(t_data *data);

/*----------------------------Init---------------------------*/

int	init(t_data *data, char **av, int ac);

/*----------------------------Atoi---------------------------*/

int	ft_atoi(const char *str);

/*---------------------------Utils---------------------------*/

void	ft_exit(t_data *data);
int	ft_error(char *str, t_data *data);
int	check_input(char **av);
int	ft_strcmp(char *s1, char *s2);

/*--------------------------Utils_2--------------------------*/

u_int64_t	get_time(void);
int	ft_usleep(useconds_t time);
void	print(char *str, t_philo *philo);

#endif