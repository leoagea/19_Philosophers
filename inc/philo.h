/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lagea < lagea@student.s19.be >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:25:35 by lagea             #+#    #+#             */
/*   Updated: 2024/08/12 00:44:35 by lagea            ###   ########.fr       */
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
#define MAGENTA "\033[35;01m"  //SLEEP
#define GREEN "\033[32;01m"  //EAT
#define CYAN "\033[36;01m"  //THINK
#define RESET    "\033[0m"

#endif