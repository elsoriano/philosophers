/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:32:12 by rhernand          #+#    #+#             */
/*   Updated: 2025/03/22 13:16:52 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->lock));
	printf("%ld %d is sleeping\n", ft_timestamp(), philo->id);
	pthread_mutex_unlock(&(philo->data->lock));
	ft_usleep(philo->data->tts);
	ft_forensics(philo);
	pthread_mutex_lock(&(philo->data->lock));
	printf("%ld %d is thinking\n", ft_timestamp(), philo->id);
	pthread_mutex_unlock(&(philo->data->lock));
	return ;
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	pthread_mutex_lock(philo->second_fork);
	philo->last_meal = ft_timestamp();
	pthread_mutex_lock(&(philo->data->lock));
	printf("%ld %d has taken a fork\n", ft_timestamp(), philo->id);
	printf("%ld %d has taken a fork\n", ft_timestamp(), philo->id);
	printf("%ld %d is eating\n", ft_timestamp(), philo->id);
	pthread_mutex_unlock(&(philo->data->lock));
	philo->eating = 1;
	ft_usleep(philo->data->tte);
	philo->eating = 0;
	philo->eat_count += 1;
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	return ;
}

void	*ft_routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *) ph;
	while (1)
	{
		ft_forensics(philo);
		ft_eat(philo);
		if (philo->eat_count == philo->data->n_meals)
		{
			philo->finished = 1;
			printf("%ld %d finished\n", ft_timestamp(), philo->id);
			return (NULL);
		}
		ft_sleep(philo);
	}
	return (NULL);
}
