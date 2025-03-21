/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:32:12 by rhernand          #+#    #+#             */
/*   Updated: 2025/03/21 20:20:58 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	pthread_mutex_lock(philo->second_fork);
	pthread_mutex_lock(&(philo->data->lock));
	printf("%ld %d took a fork\n", ft_timestamp(), philo->id);
	printf("%ld %d took a fork\n", ft_timestamp(), philo->id);
	printf("%ld %d is eating\n", ft_timestamp(), philo->id);
	pthread_mutex_unlock(&(philo->data->lock));
	usleep(philo->data->tte);
	philo->eat_count += 1;
	philo->last_meal = ft_timestamp();
	if (philo->eat_count == philo->data->n_meals)
		philo->finished = 1;
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_lock(&(philo->data->lock));
	printf("%ld %d left a fork\n", ft_timestamp(), philo->id);
	printf("%ld %d left a fork\n", ft_timestamp(), philo->id);
	printf("%ld %d is sleeping\n", ft_timestamp(), philo->id);
	usleep(philo->data->tts);
	pthread_mutex_unlock(&(philo->data->lock));
}

void	*ft_routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *) ph;
	while (1)
	{
		ft_eat(philo);
	}
	return (NULL);
}
