/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhernand <rhernand@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 19:00:22 by rhernand          #+#    #+#             */
/*   Updated: 2025/03/30 16:52:29 by rhernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	int				id;
	struct s_data	*data;
	int				eat_count;
	int				eating;
	int				finished;
	uint64_t		last_meal;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
}		t_philo;

typedef struct s_data
{
	int					n_philo;
	t_philo				*philos;
	uint64_t			ttd;
	uint64_t			tte;
	uint64_t			tts;
	uint64_t			start;
	int					n_meals;
	int					dead;
	pthread_mutex_t		*forks;
	pthread_t			*threads;
	pthread_t			forensic;
	pthread_t			waitress;
	pthread_mutex_t		lock;
}		t_data;

int			main(int argc, char **argv);
int			ft_init(t_data *data, int argc, char **argv);
int			ft_args_fill(t_data *data, int argc, char **argv);
void		ft_place_forks(t_data *data);
int			ft_init_philos(t_data *data);
int			ft_alloc_data(t_data *data);
void		ft_free(t_data *data);
void		ft_free_forks(t_data *data);
uint64_t	ft_timestamp(t_data *data);
void		ft_usleep(uint64_t ms, t_data *data);
void		*ft_routine(void *ph);
void		ft_eat(t_philo *philo);
int			ft_init_threads(t_data *data);
void		ft_join_threads(t_data *data);
void		ft_detach_threads(t_data *data);
int			ft_forensics(t_data *data);
int			ft_waitress(t_data *data, int j);
void		ft_checks(t_data *data);
int			ft_atoi(const char *str);

#endif