#include "../../lib/philo.h"

void	*monitor(void *data_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) data_pointer;
	while (check_death(philo->data) == 0)
	{
		if (check_finished(philo->data) >= philo->data->philo_num)
			change_death(philo->data);
		ft_usleep(1);
	}
	return ((void *)0);
}

void	*supervisor(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	while (check_death(philo->data) == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->time_to_die && philo->eating == 0)
		{
			messages(DIED, philo);
		}
		if (philo->eat_cont == philo->data->meals_nb)
		{
			pthread_mutex_lock(&philo->data->lock_finished);
			philo->data->finished++;
			pthread_mutex_unlock(&philo->data->lock_finished);
			philo->eat_cont++;
		}
		pthread_mutex_unlock(&philo->lock);
		ft_usleep(1);
	}
	return ((void *)0);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	philo->time_to_die = philo->data->death_time + get_time();
	pthread_mutex_lock(&philo->data->lock);
	if (pthread_create(&philo->t1, NULL, &supervisor, (void *)philo))
		return ((void *)1);
	pthread_mutex_unlock(&philo->data->lock);
	while (check_death(philo->data) == 0
		&& check_finished(philo->data) != philo->data->philo_num)
	{
		if (philo->id % 2 && philo->data->philo_num % 2
			&& philo->data->philo_num != 1)
			ft_usleep(philo->data->eat_time / 2);
		eat(philo);
		messages(THINKING, philo);
	}
	if (pthread_join(philo->t1, NULL))
		return ((void *)1);
	return ((void *)0);
}

int	thread_init0(t_data *data)
{
	int		i;

	i = 1;
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&data->lock);
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			return (error(TH_ERR, data));
		pthread_mutex_unlock(&data->lock);
		ft_usleep(1);
		i += 2;
	}
	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&data->lock);
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			return (error(TH_ERR, data));
		pthread_mutex_unlock(&data->lock);
		ft_usleep(1);
		i += 2;
	}
	return (0);
}

int	thread_init(t_data *data)
{
	int			i;
	pthread_t	t0;

	t0 = 0;
	data->start_time = get_time();
	if (data->meals_nb > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, &data->philos[0]))
			return (error(TH_ERR, data));
	}
	pthread_detach(t0);
	thread_init0(data);
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->tid[i], NULL))
			return (error(JOIN_ERR, data));
	}
	return (0);
}
