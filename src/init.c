/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 19:24:22 by rhernand          #+#    #+#             */
/*   Updated: 2025/03/23 18:37:49 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_place_forks(t_data *data)
{
	int	i;

	if (!data->philos || !data->forks)
		return ;
	data->philos[0].first_fork = &(data->forks[0]);
	data->philos[0].second_fork = &(data->forks[data->n_philo - 1]);
	i = 1;
	while (i < data->n_philo)
	{
		if (i % 2 != 0)
		{
			data->philos[i].second_fork = &(data->forks[i]);
			data->philos[i].first_fork = &(data->forks[i - 1]);
		}
		else
		{
			data->philos[i].first_fork = &(data->forks[i]);
			data->philos[i].second_fork = &(data->forks[i - 1]);
		}
		i++;
	}
}

int	ft_init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		data->philos[i].eat_count = 0;
		data->philos[i].finished = 0;
		data->philos[i].id = i + 1;
		data->philos[i].eating = 0;
		data->philos[i].data = data;
		i++;
	}
	ft_place_forks(data);
	return (0);
}

int	ft_alloc_data(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->n_philo);
	if (!data->philos)
		return (printf("Error allocating philos"), 1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->forks)
	{
		free(data->philos);
		return (printf("Error allocating forks"), 1);
	}
	i = 0;
	while (i++ < data->n_philo)
		pthread_mutex_init(&(data->forks[i - 1]), NULL);
	data->threads = malloc(sizeof(pthread_t) * data->n_philo);
	if (!data->threads)
	{
		free(data->forks);
		free(data->philos);
		return (printf("Error allocating threads"), 1);
	}
	return (0);
}

int	ft_args_fill(t_data *data, int argc, char **argv)
{
	if (!data)
		return (1);
	if (argc < 5 || argc > 6)
		return (printf("Invalid number of Arguments\n"), 1);
	if (ft_atoi((const char *) argv[1]) <= 0)
		return (printf("Wrong No of Philosophers\n"), 1);
	data->n_philo = ft_atoi((const char *) argv[1]);
	if (ft_atoi((const char *) argv[2]) <= 0)
		return (printf("Wrong Time to Die\n"), 1);
	data->ttd = (uint64_t) ft_atoi((const char *) argv[2]);
	if (ft_atoi((const char *) argv[3]) <= 0)
		return (printf("Wrong Time to Eat\n"), 1);
	data->tte = (uint64_t) ft_atoi((const char *) argv[3]);
	if (ft_atoi((const char *) argv[4]) <= 0)
		return (printf("Wrong Time to Sleep\n"), 1);
	data->tts = (uint64_t) ft_atoi((const char *) argv[4]);
	if (argc == 6)
	{
		if (ft_atoi((const char *) argv[5]) <= 0)
			return (printf("Wrong No of Meals\n"), 1);
		data->n_meals = ft_atoi((const char *) argv[5]);
	}
	pthread_mutex_init(&(data->lock), NULL);
	data->dead = 0;
	return (0);
}

int	ft_init(t_data *data, int argc, char **argv)
{
	if (ft_args_fill(data, argc, argv))
		return (1);
	if (ft_alloc_data(data))
		return (1);
	if (ft_init_philos(data))
		return (1);
	return (0);
}
