/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:28:19 by rhernand          #+#    #+#             */
/*   Updated: 2025/03/21 21:36:53 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_waitress(t_data *data, int j)
{
	while (data->philos[j].finished == 1 && j < data->n_philo)
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
			if (data->philos[i].last_meal + data->ttd < ft_timestamp() && \
					data->philos[i].eating == 0)
			{
				ft_join_threads(data);
				printf("%ld %d died\n", ft_timestamp(), i + 1);
				ft_free(data);
				exit(EXIT_SUCCESS);
			}
			usleep(1000);
			i++;
		}
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
}

int64_t	ft_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	data;

	if (ft_init(&data, argc, argv))
		return (1);
	if (data.n_philo == 1)
	{
		if (usleep(data.ttd))
			printf("Error in usleep\n");
		printf("%ld 1 Died\n", ft_timestamp());
	}
	else
		ft_init_threads(&data);
	ft_checks(&data);
	return (0);
}
