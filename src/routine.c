/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea <lagea@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:01:36 by lagea             #+#    #+#             */
/*   Updated: 2024/08/09 17:46:59 by lagea            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void print(t_data *data, t_philo *philo, int mode)
{
    pthread_mutex_lock(&philo->print);
    if (mode == FORK && data->dead == 0)
        printf("[%zd] [%d]"BLUE" has taken a fork"RESET"\n", get_current_time() - data->start, philo->id);
    else if (mode == EAT && data->dead == 0)
        printf("[%zd] [%d]"GREEN" is eating"RESET"\n", get_current_time() - data->start, philo->id);
    else if (mode == SLEEP && data->dead == 0)
        printf("[%zd] [%d]"MAGENTA" is sleeping"RESET"\n", get_current_time() - data->start, philo->id);
    else if (mode == THINK && data->dead == 0)
        printf("[%zd] [%d]"CYAN" is thinking"RESET"\n", get_current_time() - data->start, philo->id);
    pthread_mutex_unlock(&philo->print);
}

void eat(t_data *data, t_philo *philo)
{
    // philo->meals_eaten++;
    // printf("Test\n");
    pthread_mutex_lock(philo->l_fork);
    // printf("Test 1\n");
    print(data, philo, FORK);
    if (data->nb_philo == 1)
    {
        // printf("Test 2\n");
        precise_usleep(data->t_to_die * 1000);
        // printf("Test 3\n");
        print(data, philo, DEAD);
        // printf("Test 4\n");
        pthread_mutex_unlock(philo->l_fork);
        // printf("Test 5\n");
        data->dead = 1;
        return ;
    }
    pthread_mutex_lock(philo->r_fork);
    print(data, philo, FORK);
    print(data, philo, EAT);
    precise_usleep(data->t_to_eat * 1000);
    philo->meals_eaten++;
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
    philo->last_eat = get_current_time();
}

void *routine(void *p)
{
    t_philo *philo;
    t_data *data;

    philo = (t_philo *)p;
    data = philo->data;
    if ((philo->id % 2) == 0)
        precise_usleep((data->t_to_sleep / 2) * 1000);
    while(data->dead != 1 || data->all_eaten <= data->nb_philo)
    {
        eat(data, philo);
        print(data, philo, SLEEP);
        precise_usleep(data->t_to_sleep * 1000);
        if (data->dead >= 1)
        {
            // printf("Test 6\n");
            return NULL;
        }
        if (philo->meals_eaten == data->nb_must_eat)
            data->all_eaten++;
        print(data, philo, THINK);
    }
    return NULL;
}

static void check_death(t_data *data, int i)
{
    if((get_current_time() - data->philos[i].last_eat) > (size_t)data->t_to_die)
    {
        pthread_mutex_lock(&data->philos[i].monitoring);
        // pthread_mutex_lock(&data->philos[i].print);
        if(data->dead == 0)
        {
            printf("[%zd] [%d]"RED" died"RESET"\n", get_current_time() - data->start, data->philos[i].id);
            data->dead = 1;
        }
        pthread_mutex_unlock(&data->philos[i].monitoring);
        // pthread_mutex_unlock(&data->philos[i].print);
        return ;
    }
}

void monitoring(t_data *data)
{
    int i;

    while(data->dead != 1 && data->all_eaten <= data->nb_philo)
    {
        // printf("data->dead : %d\n", data->dead);
        // printf("Test 7\n");
        i = -1;
        while(++i < data->nb_philo)
        {
            // printf("Test 8\n");
            pthread_mutex_lock(&data->philos[i].eat);
            if (data->all_eaten == data->nb_philo)
            {
                pthread_mutex_unlock(&data->philos[i].eat);
                return ;
            }
            check_death(data, i);
            pthread_mutex_unlock(&data->philos[i].eat);
        }
    }
    return ;
}
