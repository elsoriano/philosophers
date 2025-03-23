/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:28:19 by rhernand          #+#    #+#             */
/*   Updated: 2025/03/23 18:33:44 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ft_forensics(t_philo *philo)
{
	if (philo->last_meal + philo->data->ttd < ft_timestamp() && \
					philo->eating == 0)
	{
		pthread_mutex_lock(&(philo->data->lock));
		ft_detach_threads(philo->data);
		printf("%ld %d died\n", ft_timestamp(), philo->id);
		ft_free(philo->data);
		exit(EXIT_SUCCESS);
	}
}

int	ft_waitress(t_data *data, int j)
{
	while (j < data->n_philo && data->philos[j].finished == 1)
		j++;
	if (j == data->n_philo)
	{
		ft_join_threads(data);
		printf("All Philosophers Eat %d Times\n", data->n_meals);
		ft_free(data);
		exit(0);
	}
	return (j);
}

void	ft_checks(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (1)
	{
		while (i < data->n_philo)
		{
			j = ft_waitress(data, j);
			ft_forensics(&(data->philos[i]));
			i++;
		}
		ft_usleep(10);
		i = 0;
	}
}

void	ft_init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&(data->threads[i]), NULL, \
			ft_routine, &(data->philos[i])))
		{
			printf("Error in pthread_create\n");
			ft_free(data);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return ;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (ft_init(&data, argc, argv))
		return (1);
	if (data.n_philo == 1)
	{
		if (usleep(data.ttd))
			printf("Error in usleep\n");
		printf("%ld 1 Died\n", ft_timestamp());
		return (0);
	}
	else
		ft_init_threads(&data);
	ft_checks(&data);
	return (0);
}
