/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:25:35 by lagea             #+#    #+#             */
/*   Updated: 2024/08/08 17:04:36 by lagea            ###   ########.fr       */
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

#define FORK 0
#define EAT 1
#define SLEEP 2
#define THINK 3
#define DEAD 4
#define RED "\033[1;31m" //DIED
#define BLUE "\033[34;01m"  //FORK
#define MAGENTA "\033[35;01m"  //SLEEP
#define GREEN "\033[32;01m"  //EAT
#define CYAN "\033[36;01m"  //THINK
#define RESET    "\033[0m"

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	atomic_long		last_eat;
	pthread_mutex_t	eat;
	pthread_mutex_t	print;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	size_t			start_time;
	pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				nb_must_eat;
	int				all_eaten;
	int				dead;// 0 if no dead philo, 1 if 1 one philo just died
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

/*-------------------------------Routine-------------------------------*/

void *routine(void *p);

#endif