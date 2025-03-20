/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:32:12 by rhernand          #+#    #+#             */
/*   Updated: 2025/03/20 15:46:38 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*ft_routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *) ph;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		printf("left fork locked\n");
		pthread_mutex_lock(philo->r_fork);
		printf("right fork locked\n");
		printf("%ld %d is eating\n", ft_timestamp(), philo->id);
		usleep(philo->data->tte);
		pthread_mutex_unlock(philo->l_fork);
		printf("left fork unlocked\n");
		pthread_mutex_unlock(philo->r_fork);
		printf("right fork unlocked\n");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		printf("right fork locked\n");
		pthread_mutex_lock(philo->l_fork);
		printf("left fork locked\n");
		printf("%ld %d is eating\n", ft_timestamp(), philo->id);
		usleep(philo->data->tte);
		pthread_mutex_unlock(philo->r_fork);
		printf("right fork unlocked\n");
		pthread_mutex_unlock(philo->l_fork);
		printf("left fork unlocked\n");
	}
	return (NULL);
}
