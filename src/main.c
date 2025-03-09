/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:28:19 by rhernand          #+#    #+#             */
/*   Updated: 2025/03/09 20:56:04 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_data_fill(t_data *data, int argc, char **argv)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (argc < 5 || argc > 6)
		return (printf("Invalid number of Arguments\n"), 1);
	data->n_philo = ft_atoi((const char *) argv[1]);
	if (data->n_philo <= 0)
		return (printf("Wrong No of Philosophers"), 1);
	data->ttd = (uint64_t) ft_atoi((const char *) argv[2]);
	if (data->ttd <= 0)
		return (printf("Wrong Time to Die"), 1);
	data->tte = (uint64_t) ft_atoi((const char *) argv[3]);
	if (data->tte <= 0)
		return (printf("Wrong Time to Eat"), 1);
	data->tts = (uint64_t) ft_atoi((const char *) argv[3]);
	if (data->tts <= 0)
		return (printf("Wrong Time to Sleep"), 1);
	if (argc == 5)
	{
		data->n_meals = ft_atoi((const char *) argv[4]);
		if (data->n_meals <= 0)
			return (printf("Wrong No of Meals"), 1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (ft_data_fill(&data, argc, argv))
		return (1);
	return (0);
}