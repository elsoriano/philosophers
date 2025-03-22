/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:32:12 by rhernand          #+#    #+#             */
/*   Updated: 2025/03/22 11:39:10 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_eat(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->first_fork);
		pthread_mutex_lock(philo->second_fork);
		pthread_mutex_lock(&(philo->data->lock));
		printf("%ld %d took a fork\n", ft_timestamp(), philo->id);
		printf("%ld %d took a fork\n", ft_timestamp(), philo->id);
		printf("%ld %d is eating\n", ft_timestamp(), philo->id);
		pthread_mutex_unlock(&(philo->data->lock));
		philo->eating = 1;
		ft_usleep(philo->data->tte);
		philo->eating = 0;
		philo->eat_count += 1;
		philo->last_meal = ft_timestamp();
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
		pthread_mutex_lock(&(philo->data->lock));
		printf("%ld %d left a fork\n", ft_timestamp(), philo->id);
		printf("%ld %d left a fork\n", ft_timestamp(), philo->id);
		printf("%ld %d is sleeping\n", ft_timestamp(), philo->id);
		pthread_mutex_unlock(&(philo->data->lock));
		if (philo->eat_count == philo->data->n_meals)
		{
			philo->finished = 1;
			printf("%ld %d finished\n", ft_timestamp(), philo->id);
			return ;
		}
		ft_usleep(philo->data->tts);
		pthread_mutex_lock(&(philo->data->lock));
		printf("%ld %d is thinking\n", ft_timestamp(), philo->id);
		pthread_mutex_unlock(&(philo->data->lock));
	}
}

void	*ft_routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *) ph;
	ft_eat(philo);
	return (NULL);
}
